#pragma once
#include "Soli-Rom.h"
#include "RectInfo.h"

class CollisionMapper : public SoliRom::Layer
{
public:
	CollisionMapper();
	~CollisionMapper() = default;

	virtual void OnEvent() override;
	virtual void OnUpdate() override;

	void save();

private:
	std::vector<SDL_Rect> farts;
	std::vector<SDL_Rect> drawFarts;

	SoliRom::App* app;

	std::string mapPath;
	std::string collisionMapName;

	SoliRom::Asset::Texture* t_map;
	SoliRom::Asset::Texture* t_text;

	SoliRom::EngineObject g_map;
	SoliRom::EngineObject g_text;

	SoliRom::Window* w_map;
	SoliRom::Window* w_rect;

	std::vector<RectInfo*> test;

	SoliRom::Camera cam;

	bool creating = false;
	int clickWorldPosX, clickWorldPosY;

	bool saveToggle = false;
};

