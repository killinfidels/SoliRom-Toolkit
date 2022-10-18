#pragma once
#include "Soli-Rom.h"

class RectInfo
{
public:
	RectInfo(int _i, SDL_Rect* rect);
	~RectInfo();

	static void init();
	void update();
	void draw();

private:
	static SDL_Color black;
	static SoliRom::AssetManager* am;
	static int textSize;
	int id;
	SDL_Rect* assignedRect;
	SDL_Rect previous;

	static SoliRom::Asset::Texture* t_x;
	static SoliRom::Asset::Texture* t_y;
	static SoliRom::Asset::Texture* t_w;
	static SoliRom::Asset::Texture* t_h;
	SoliRom::Asset::Texture* t_xValue;
	SoliRom::Asset::Texture* t_yValue;
	SoliRom::Asset::Texture* t_wValue;
	SoliRom::Asset::Texture* t_hValue;
	SoliRom::Asset::Texture* t_id;

	SoliRom::EngineObject g_x;
	SoliRom::EngineObject g_y;
	SoliRom::EngineObject g_w;
	SoliRom::EngineObject g_h;
	SoliRom::EngineObject g_xValue;
	SoliRom::EngineObject g_yValue;
	SoliRom::EngineObject g_wValue;
	SoliRom::EngineObject g_hValue;
	SoliRom::EngineObject g_id;
};