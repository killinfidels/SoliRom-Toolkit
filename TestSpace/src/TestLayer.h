#pragma once
#include "Soli-Rom.h"

struct point
{
	int x, y, z;
};

class obj_3D : public SoliRom::GameObject
{
public:
	void setZ(int _z) { z = _z; }
	int getZ() { return z; }
	void drawRect() { if (visible) { SDL_RenderDrawRect(renderer, &renderRect); } }
	void draw() { if (visible) { SDL_RenderCopy(renderer, texture->get(), NULL, &renderRect); } }
	static void setTexture(SoliRom::Asset::Texture* _texture) { texture = _texture; }
	static void setRenderer(SoliRom::Window* _window) { renderer = _window->getSDL_Renderer(); }
	void setRenderRect(SDL_Rect _rect) { renderRect = _rect; }
private:
	SDL_Rect renderRect;
	int z;
	static SDL_Renderer* renderer;
	static SoliRom::Asset::Texture* texture;
};

class TestLayer : public SoliRom::Layer
{
public:
	TestLayer();
	~TestLayer() = default;

	virtual void onUpdate() override;
	//virtual void onEvent() override;
private:

	struct camera
	{
		point pos;
		int middleX, middleY;
		int middleX2, middleY2;
		int screenDistance;
		int camSpeed;
		//degrees
		int xD, yD;
	};


	point pointToScreen(int _x, int _y, int _z);
	void objSetScreenRect(obj_3D* _obj);
	void draw2D();
	void drawRoad();
	void vertexRender();

	SoliRom::Window* w_3DTest;
	SoliRom::Window* w_2DTest;

	camera cam;
	SoliRom::Asset::Texture t_tree;
	obj_3D tree[24];
	SoliRom::Asset::Texture t_road;
	SoliRom::Asset::Texture t_road2;
};