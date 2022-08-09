#pragma once
#include"Soli-Rom.h"

class Scene
{
public:
	Scene()
	{

	}
protected:
	void load();

	void script();

	void sceneTransition();

	void draw();

	SDL_Texture* background;
};

class Shack : public Scene
{
public:
	static Shack* getInstance();
	~Shack();
private:
	Shack()
	{
		
	}
	static Shack* instance;

	SoliRom::Texture shackTexture;
};
