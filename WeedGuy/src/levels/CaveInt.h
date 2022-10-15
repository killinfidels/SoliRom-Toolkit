#pragma once
#include "../core.h"
#include "Level.h"
#include "../objects/Items.h"
#include "../objects/Object.h"

struct Camera3D
{
	int x, y, z;
	int screenDistance = 1500;
};

class CaveWalls
{
public:
	CaveWalls();
	~CaveWalls();

	static void LoadTextureAndCamera(std::string _path, Camera3D* _cam);
	void DrawRect();
	void Draw();

	int z;

	bool visible;
private:
	static SoliRom::Asset::Texture* texture;
	static Camera3D* cam;
	static SDL_Rect rect;
	SDL_Rect renderRect;
	void rect3D();

};



class CaveInt : public Level
{
	CaveInt();
	static CaveInt* instance;

public:
	static CaveInt* Get();
	~CaveInt();

	virtual void Load(LevelId _previousLevel) override;
	virtual void Script() override;
	virtual void Draw() override;
	//virtual void Quit() override;
	virtual LevelId LevelTransition() override;

private:
	SoliRom::Asset::Texture* t_background;
	SoliRom::Asset::Texture* t_arrowDown;

	Camera3D cam;
	Object level;
	Object caveLayers;
	Object back;

	std::vector<CaveWalls> caveTunnels;
	const int wallSpacing = 250;
};
