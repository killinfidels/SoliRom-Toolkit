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

	SoliRom::GameObject g_x;
	SoliRom::GameObject g_y;
	SoliRom::GameObject g_w;
	SoliRom::GameObject g_h;
	SoliRom::GameObject g_xValue;
	SoliRom::GameObject g_yValue;
	SoliRom::GameObject g_wValue;
	SoliRom::GameObject g_hValue;
	SoliRom::GameObject g_id;
};