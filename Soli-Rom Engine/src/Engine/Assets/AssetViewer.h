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

		int scale = 5;
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

		SDL_Rect selectedBox;
		int selectedBoxId = -1;
		SDL_Rect selectedAssetType;

		Selection currentSelection;
		Selection boxesLoadedFlag;

		//Assets
		std::vector<Asset::Texture> textures;
		std::vector<Asset::Animation> animations;
		std::vector<Asset::Sound> sounds;

		GameObject splash;
			Asset::Texture* t_Splash;

		GameObject header;
			Asset::Texture* t_Header;

		GameObject updateButton;
			Asset::Texture* t_UpdateButton;

		GameObject
			texturesButton,
			animationsButton,
			soundsButton;

		Asset::Texture
			*t_TexturesButton,
			*t_AnimationsButton,
			*t_SoundsButton;


		GameObject assetList;
			Asset::Texture* t_AssetList;

		GameObject assetWindow;
			Asset::Texture* t_AssetWindow;

		GameObject assetWindowBorder;
			Asset::Texture* t_AssetWindowBorder;


		GameObject arrowUpList;
			Asset::Texture* t_ArrowUpList;
		GameObject arrowDownList;
			Asset::Texture* t_ArrowDownList;

		GameObject arrowUpWindow;
			Asset::Texture* t_ArrowUpWindow;
		GameObject arrowDownWindow;
			Asset::Texture* t_ArrowDownWindow;

		GameObject scrollBarBorderList1, scrollBarBorderList2, scrollBarMiddleList;
		Asset::Texture
			* t_ScrollBarBorderList,
			* t_ScrollBarMiddleList;

		GameObject scrollBarBorderWindow1, scrollBarBorderWindow2, scrollBarMiddleWindow;
			Asset::Texture
				* t_ScrollBarBorderWindow,
				* t_ScrollBarMiddleWindow;

		std::vector<GameObject> boxes;
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

		Asset::Texture* CreateTexture(std::string _path);
		void LoadTexture(Asset::Texture* _texture);
		void UnloadTexture(Asset::Texture* _texture);
	};
}