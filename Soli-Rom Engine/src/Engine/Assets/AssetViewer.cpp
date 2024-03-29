#include "precompiledheaders.h"
#include "AssetViewer.h"
#include "Engine/Input.h"

namespace SoliRom
{
	AssetViewer::AssetViewer() : Layer("Asset Viewer Layer")
	{
		app = App::Get();
		manager = AssetManager::Get();

		running = false;
		toggle = false;

		currentSelection = Selection::ENDOFLIST;
		boxesLoadedFlag = Selection::ENDOFLIST;

		assetsLoaded = { false, false, false };

		t_Header = CreateTexture("Engine/Header.png");
		t_UpdateButton = CreateTexture("Engine/Update.png");
		t_AssetList = CreateTexture("Engine/AssetList.png");
		t_AssetWindow = CreateTexture("Engine/AssetWindow.png");
		t_AssetWindowBorder = CreateTexture("Engine/AssetWindowBorder.png");
		t_Splash = CreateTexture("Engine/Loading.png");
		t_Box = CreateTexture("Engine/Box.png");

		t_ArrowUpList = CreateTexture("Engine/ArrowUpList.png");
		t_ArrowDownList = CreateTexture("Engine/ArrowDownList.png");
		t_ArrowUpWindow = CreateTexture("Engine/ArrowUpWindow.png");
		t_ArrowDownWindow = CreateTexture("Engine/ArrowDownWindow.png");

		t_ScrollBarBorderList = CreateTexture("Engine/ScrollListBorder.png");
		t_ScrollBarMiddleList = CreateTexture("Engine/ScrollListMiddle.png");
		t_ScrollBarBorderWindow = CreateTexture("Engine/ScrollWindowBorder.png");
		t_ScrollBarMiddleWindow = CreateTexture("Engine/ScrollWindowMiddle.png");

		t_TexturesButton = CreateTexture("Engine/TextBox.png");
		t_AnimationsButton = CreateTexture("Engine/TextBox.png");
		t_SoundsButton = CreateTexture("Engine/TextBox.png");

		InitUIRects();

		UpdateAssetList();
	}

	void AssetViewer::OnEvent()
	{
		//open close window
		if (Input::keyPressed(SDLK_F11))
		{
			if (!toggle)
			{
				toggle = !toggle;
				running = !running;

				if (running)
				{
					Open();
				}
				else
				{
					Close();
				}
			}
		}
		else if (toggle)
		{
			toggle = !toggle;
		}

		if (running)
		{
			//everything Clicking related :)
			if (Input::Click())
			{
				//textures button - runs if not already selected
				if (Input::MouseInRect(texturesButton.GetScreenRect()))
				{
					if (currentSelection != Selection::TEXTURES)
					{
						ClearBoxes();
						currentSelection = Selection::TEXTURES;
						boxesLoadedFlag = ENDOFLIST;
						selectedAssetType = *texturesButton.GetRect();
					}
				}

				////animations button - runs if not already selected
				if (Input::MouseInRect(animationsButton.GetScreenRect()))
				{
					if (currentSelection != Selection::ANIMATIONS)
					{
						ClearBoxes();
						currentSelection = Selection::ANIMATIONS;
						boxesLoadedFlag = ENDOFLIST;
						selectedAssetType = *animationsButton.GetRect();
					}
				}

				//sound button - runs if not already selected
				if (Input::MouseInRect(soundsButton.GetScreenRect()))
				{
					if (currentSelection != Selection::SOUNDS)
					{
						ClearBoxes();
						currentSelection = Selection::SOUNDS;
						boxesLoadedFlag = ENDOFLIST;
						selectedAssetType = *soundsButton.GetRect();
					}
				}

				//update button
				if (Input::MouseInRect(updateButton.GetScreenRect()))
				{
					update = true;
				}

				//flag for box clicked
				bool tempboxclicked = false;

				//box clicks
				for (int i = 0; i < boxes.size(); i++)
				{
					if (Input::MouseInRect(boxes[i]->GetScreenRect()))
					{
						selectedBox = *boxes[i]->GetRect();
						selectedBoxId = i;
						tempboxclicked = true;
					}
				}

				//hides box if nothing is selected
				if (!tempboxclicked)
				{
					selectedBox.x = -10000;
					selectedBoxId = -1;
				}
			}
		}
	}

	void AssetViewer::Draw()
	{
		SDL_RenderClear(window->getSDL_Renderer());

		//draw
		assetList.Draw();
		assetWindow.Draw();

		arrowUpList.Draw();
		arrowDownList.Draw();
		scrollBarBorderList1.Draw();
		scrollBarBorderList2.Draw();
		scrollBarMiddleList.Draw();

		arrowUpWindow.Draw();
		arrowDownWindow.Draw();
		scrollBarBorderWindow1.Draw();
		scrollBarBorderWindow2.Draw();
		scrollBarMiddleWindow.Draw();

		texturesButton.Draw();
		animationsButton.Draw();
		soundsButton.Draw();

		for (int i = 0; i < boxes.size(); i++)
		{
			SDL_FRect tempBoxBackground = *boxes[i]->GetRect();
			tempBoxBackground.x -= 1 * scale;
			tempBoxBackground.y -= 1 * scale;
			tempBoxBackground.w += 2 * scale;
			tempBoxBackground.h += 2 * scale;
			SDL_RenderCopyF(window->getSDL_Renderer(), t_Box->Get(), NULL, &tempBoxBackground);
			boxes[i]->Draw();
		}

		assetWindowBorder.Draw();

		header.Draw();

		SDL_SetRenderDrawColor(window->getSDL_Renderer(), 255, 0, 0, 255);

		SDL_RenderDrawRectF(window->getSDL_Renderer(), &selectedBox);
		SDL_RenderDrawRectF(window->getSDL_Renderer(), &selectedAssetType);

		SDL_SetRenderDrawColor(window->getSDL_Renderer(), 255, 255, 255, 255);

		updateButton.Draw();

		SDL_RenderPresent(window->getSDL_Renderer());
	}

	void AssetViewer::OnUpdate()
	{
		if (running)
		{
			if (update)
			{
				LoadAssets();

				update = !update;
			}

			SetBoxes();

			//update animations
			if (currentSelection == ANIMATIONS)
			{
				for (int i = 0; i < boxes.size(); i++)
				{
					boxes[i]->SetTexture(animations[i].Get());
				}
			}

			Draw();
		}

	}

	void AssetViewer::Open()
	{

		window = app->CreateWindow("Asset Viewer", scale * 150, scale * 120);

		//Draw splash here
		SDL_RenderClear(window->getSDL_Renderer());
		LoadTexture(t_Splash);
		splash.SetTexture(t_Splash);
		splash.Draw();

		SDL_RenderPresent(window->getSDL_Renderer());

		LoadTexture(t_Header);
		LoadTexture(t_UpdateButton);
		LoadTexture(t_AssetList);
		LoadTexture(t_AssetWindow);
		LoadTexture(t_AssetWindowBorder);
		LoadTexture(t_ArrowUpList);
		LoadTexture(t_ArrowDownList);
		LoadTexture(t_ScrollBarBorderList);
		LoadTexture(t_ScrollBarMiddleList);
		LoadTexture(t_ArrowUpWindow);
		LoadTexture(t_ArrowDownWindow);
		LoadTexture(t_ScrollBarBorderWindow);
		LoadTexture(t_ScrollBarMiddleWindow);
		LoadTexture(t_TexturesButton);
		LoadTexture(t_AnimationsButton);
		LoadTexture(t_SoundsButton);
		LoadTexture(t_Box);

		header.SetTexture(t_Header);
		updateButton.SetTexture(t_UpdateButton);
		assetList.SetTexture(t_AssetList);
		assetWindow.SetTexture(t_AssetWindow);
		assetWindowBorder.SetTexture(t_AssetWindowBorder);

		arrowUpList.SetTexture(t_ArrowUpList);
		arrowDownList.SetTexture(t_ArrowDownList);
		scrollBarBorderList1.SetTexture(t_ScrollBarBorderList);
		scrollBarBorderList2.SetTexture(t_ScrollBarBorderList);
		scrollBarMiddleList.SetTexture(t_ScrollBarMiddleList);

		arrowUpWindow.SetTexture(t_ArrowUpWindow);
		arrowDownWindow.SetTexture(t_ArrowDownWindow);
		scrollBarBorderWindow1.SetTexture(t_ScrollBarBorderWindow);
		scrollBarBorderWindow2.SetTexture(t_ScrollBarBorderWindow);
		scrollBarMiddleWindow.SetTexture(t_ScrollBarMiddleWindow);

		texturesButton.SetTexture(t_TexturesButton);
		animationsButton.SetTexture(t_AnimationsButton);
		soundsButton.SetTexture(t_SoundsButton);


		assetsLoaded = { false, false, false, false};

		UpdateAssetList();
	}

	void AssetViewer::Close()
	{
		app->DestroyWindow(window->getWindowName());

		UnloadTexture(t_Splash);

		UnloadTexture(t_Header);
		UnloadTexture(t_UpdateButton);
		UnloadTexture(t_AssetList);
		UnloadTexture(t_AssetWindow);
		UnloadTexture(t_AssetWindowBorder);
		UnloadTexture(t_ArrowUpList);
		UnloadTexture(t_ArrowDownList);
		UnloadTexture(t_ScrollBarBorderList);
		UnloadTexture(t_ScrollBarMiddleList);
		UnloadTexture(t_ArrowUpWindow);
		UnloadTexture(t_ArrowDownWindow);
		UnloadTexture(t_ScrollBarBorderWindow);
		UnloadTexture(t_ScrollBarMiddleWindow);
		UnloadTexture(t_TexturesButton);
		UnloadTexture(t_AnimationsButton);
		UnloadTexture(t_SoundsButton);
		UnloadTexture(t_Box);

		textures.clear();
		animations.clear();
		sounds.clear();
	}

	bool AssetViewer::UpdateAssetList()
	{
		bool tempupdate = false;
		//textures
		if (textures.size() != manager->textures.size())
		{
			if (currentSelection == Selection::TEXTURES)
				tempupdate = true;

			assetsLoaded[TEXTURES] = false;
			textures.clear();

			for (int i = 0; i < manager->textures.size(); i++)
			{
				textures.emplace_back(Asset::Texture(manager->textures[i]->name, manager->textures[i]->path, false));
			}
		}

		//animations
		if (animations.size() != manager->animations.size())
		{
			if (currentSelection == Selection::ANIMATIONS)
				tempupdate = true;

			assetsLoaded[ANIMATIONS] = false;
			animations.clear();

			for (int i = 0; i < manager->animations.size(); i++)
			{
				animations.emplace_back(Asset::Animation(manager->animations[i]->name, manager->animations[i]->frame.front()->path));
				animations[i].frameTime = manager->animations[i]->frameTime;
			}
		}

		//sounds
		if (sounds.size() != manager->sounds.size())
		{
			if (currentSelection == Selection::SOUNDS)
				tempupdate = true;

			assetsLoaded[SOUNDS] = false;
			sounds.clear();

			for (int i = 0; i < manager->sounds.size(); i++)
			{
				sounds.emplace_back();
			}
		}

		return tempupdate;
	}

	void AssetViewer::SetBoxes()
	{
		switch (currentSelection)
		{
		case SoliRom::AssetViewer::TEXTURES:
			if (boxesLoadedFlag != TEXTURES)
			{
				if (assetsLoaded[TEXTURES])
				{
					for (int i = 0; i < textures.size(); i++)
					{
						boxes.push_back(new EngineObject);
						*boxes[i]->GetRect() = {
							scale * 59 + 30 * scale * (i % 3), scale * 26 + 26 * scale * (i / 3),
							scale * 22, scale * 22
						};
						boxes[i]->SetTexture(&textures[i]);
					}

					boxesLoadedFlag = TEXTURES;
				}

			}
			break;
		case SoliRom::AssetViewer::ANIMATIONS:
			if (boxesLoadedFlag != ANIMATIONS)
			{
				if (assetsLoaded[ANIMATIONS])
				{
					for (int i = 0; i < animations.size(); i++)
					{
						boxes.push_back(new EngineObject);
						*boxes[i]->GetRect() = {
							scale * 59 + 30 * scale * (i % 3), scale * 26 + 26 * scale * (i / 3),
							scale * 22, scale * 22
						};
						boxes[i]->SetTexture(animations[i].Get());
					}

					boxesLoadedFlag = ANIMATIONS;
				}
			}

			break;
		case SoliRom::AssetViewer::SOUNDS:
			if (boxesLoadedFlag != SOUNDS)
			{
				if (assetsLoaded[SOUNDS])
				{
					for (int i = 0; i < sounds.size(); i++)
					{
						boxes.push_back(new EngineObject);
						*boxes[i]->GetRect() = {
							scale * 59 + 30 * scale * (i % 3), scale * 26 + 26 * scale * (i / 3),
							scale * 22, scale * 22
						};
					}

					boxesLoadedFlag = SOUNDS;
				}
			}
			break;
		default:
			break;
		}
	}

	void AssetViewer::ClearBoxes()
	{
		for (int i = 0; i < boxes.size(); i++)
			delete (boxes[i]);

		boxes.clear();
	}

	void AssetViewer::InitUIRects()
	{
		*header.GetRect() = {
			scale * 0, scale * 0,
			scale * 150, scale * 20
		};

		header.UpdateRect();

		*assetList.GetRect() = {
			scale * 0, scale * 20,
			scale * 50, scale * 100
		};

		*assetWindow.GetRect() = {
			scale * 50, scale * 20,
			scale * 100, scale * 100
		};

		*assetWindowBorder.GetRect() = {
			scale * 50, scale * 20,
			scale * 100, scale * 100
		};

		*splash.GetRect() = {
			scale * 0, scale * 0,
			scale * 150, scale * 120
		};

		*updateButton.GetRect() = {
			scale * 52, scale * 109,
			scale * 31, scale * 9
		};

		*texturesButton.GetRect() = {
			scale * 2, scale * 25,
			scale * 38, scale * 9
		};

		*animationsButton.GetRect() = {
			scale * 2, scale * 25 * 2,
			scale * 38, scale * 9
		};

		*soundsButton.GetRect() = {
			scale * 2, scale * 25 * 3,
			scale * 38, scale * 9
		};

		*arrowUpList.GetRect() = {
			scale * 44, scale * 21,
			scale * 5, scale * 3
		};

		*arrowDownList.GetRect() = {
			scale * 44, scale * 116,
			scale * 5, scale * 3
		};

		*arrowUpWindow.GetRect() = {
			scale * 144, scale * 21,
			scale * 5, scale * 3
		};

		*arrowDownWindow.GetRect() = {
			scale * 144, scale * 116,
			scale * 5, scale * 3
		};


		*scrollBarBorderList1.GetRect() = {
			arrowUpList.GetRect()->x, arrowUpList.GetRect()->y + arrowUpList.GetRect()->h,
			scale * 5, scale * 1
		};

		*scrollBarMiddleList.GetRect() = {
			scrollBarBorderList1.GetRect()->x, scrollBarBorderList1.GetRect()->y + scrollBarBorderList1.GetRect()->h,
			scale * 5, scale * 1
		};

		*scrollBarBorderList2.GetRect() = {
			scrollBarMiddleList.GetRect()->x, scrollBarMiddleList.GetRect()->y + scrollBarMiddleList.GetRect()->h,
			scale * 5, scale * 1
		};

		*scrollBarBorderWindow1.GetRect() = {
			arrowUpWindow.GetRect()->x, arrowUpWindow.GetRect()->y + arrowUpWindow.GetRect()->h,
			scale * 5, scale * 1
		};

		*scrollBarMiddleWindow.GetRect() = {
			scrollBarBorderWindow1.GetRect()->x, scrollBarBorderWindow1.GetRect()->y + scrollBarBorderWindow1.GetRect()->h,
			scale * 5, scale * 1
		};

		*scrollBarBorderWindow2.GetRect() = {
			scrollBarMiddleWindow.GetRect()->x, scrollBarMiddleWindow.GetRect()->y + scrollBarMiddleWindow.GetRect()->h,
			scale * 5, scale * 1
		};
	}

	void AssetViewer::LoadAssets()
	{
		if (UpdateAssetList() || !assetsLoaded[currentSelection])
		{
			switch (currentSelection)
			{
			case SoliRom::AssetViewer::TEXTURES:
				for (int i = 0; i < textures.size(); i++)
					LoadTexture(&textures[i]);
				break;
			case SoliRom::AssetViewer::ANIMATIONS:
				for (int i = 0; i < animations.size(); i++)
				{
					animations[i].window = window;
					animations[i].Load();
					animations[i].Start();
				}
				break;
			case SoliRom::AssetViewer::SOUNDS:
				break;
			default:
				break;
			}

			assetsLoaded[currentSelection] = true;
		}
	}

	Asset::Texture* AssetViewer::CreateTexture(std::string _path)
	{
		return new Asset::Texture(_path, _path, false);
	}

	void AssetViewer::LoadTexture(Asset::Texture* _texture)
	{
		_texture->window = window;
		_texture->Load();
	}

	void AssetViewer::UnloadTexture(Asset::Texture* _texture)
	{
		_texture->window = NULL;
		_texture->texture = NULL;
	}
}