#pragma once
#include "Engine/Windows/Layer.h"
#include "AssetManager.h"
#include "Engine/Engine Objects/GameObject.h"

namespace SoliRom
{
	//extern class App;

	class AssetViewer : public Layer
	{
	public:
		AssetViewer();
		~AssetViewer() = default;

		virtual void OnUpdate() override;
		virtual void OnEvent() override;

		float scale = 5;
	private:
		App* app;
		AssetManager* manager;
		Window* window;

		enum Selection
		{
			TEXTURES,
			ANIMATIONS,
			SOUNDS,
			ENDOFLIST
		};

		SDL_FRect selectedBox;
		int selectedBoxId = -1;
		SDL_FRect selectedAssetType;

		Selection currentSelection;
		Selection boxesLoadedFlag;

		//Assets
		std::vector<Asset::Texture> textures;
		std::vector<Asset::Animation> animations;
		std::vector<Asset::Sound> sounds;

		EngineObject splash;
			Asset::Texture* t_Splash;

		EngineObject header;
			Asset::Texture* t_Header;

		EngineObject updateButton;
			Asset::Texture* t_UpdateButton;

		EngineObject
			texturesButton,
			animationsButton,
			soundsButton;

		Asset::Texture
			*t_TexturesButton,
			*t_AnimationsButton,
			*t_SoundsButton;


		EngineObject assetList;
			Asset::Texture* t_AssetList;

		EngineObject assetWindow;
			Asset::Texture* t_AssetWindow;

		EngineObject assetWindowBorder;
			Asset::Texture* t_AssetWindowBorder;


		EngineObject arrowUpList;
			Asset::Texture* t_ArrowUpList;
		EngineObject arrowDownList;
			Asset::Texture* t_ArrowDownList;

		EngineObject arrowUpWindow;
			Asset::Texture* t_ArrowUpWindow;
		EngineObject arrowDownWindow;
			Asset::Texture* t_ArrowDownWindow;

		EngineObject scrollBarBorderList1, scrollBarBorderList2, scrollBarMiddleList;
		Asset::Texture
			* t_ScrollBarBorderList,
			* t_ScrollBarMiddleList;

		EngineObject scrollBarBorderWindow1, scrollBarBorderWindow2, scrollBarMiddleWindow;
			Asset::Texture
				* t_ScrollBarBorderWindow,
				* t_ScrollBarMiddleWindow;

		std::vector<EngineObject*> boxes;
		Asset::Texture* t_Box;
		const int horizontalBoxAmount = 4;


		//flags
		bool running, toggle, update;
		std::vector<bool> assetsLoaded;


		void Open();
		void Close();

		void Draw();

		bool UpdateAssetList();
		void LoadAssets();
		void SetBoxes();
		void ClearBoxes();
		void InitUIRects();

		Asset::Texture* CreateTexture(std::string _path);
		void LoadTexture(Asset::Texture* _texture);
		void UnloadTexture(Asset::Texture* _texture);
	};
}