#pragma once

class Object : public SoliRom::GameObject
{
public:
	void draw();

	void draw(SDL_RendererFlip _flip);

	void drawRect(bool defaultColor);

	//move that amount left or right
	void move(int _x, int _y);

	void setTexture(SoliRom::Asset::Texture* _texture);

protected:

	void CheckRender();

	SDL_Texture* texture = NULL;
	SDL_Renderer* renderer = NULL;
};