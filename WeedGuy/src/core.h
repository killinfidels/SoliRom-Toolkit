#pragma once
#include "Soli-Rom.h"
#include <stdio.h>
#include <conio.h>
#include <chrono>

const float scale = 1;

SoliRom::Window* getWindow();

class things : public SoliRom::GameObject
{
private:
public:
	SDL_Rect* reScale()
	{
		scaled.x = getRect()->x * scale;
		scaled.y = getRect()->y * scale;
		scaled.w = getRect()->w * scale;
		scaled.h = getRect()->h * scale;

		return &scaled;
	}
	SDL_Texture* texture;

	float sizeMul = 1;
	void draw()
	{
		reScale();
		SDL_RenderCopy(getWindow()->getSDL_Renderer(), texture, NULL, &scaled);
	}

	void draw(SDL_RendererFlip _flip)
	{
		reScale();
		SDL_RenderCopyEx(getWindow()->getSDL_Renderer(), texture, NULL, &scaled, NULL, NULL, _flip);
	}

	void drawRect(bool defaultColor)
	{
		reScale();
		if (defaultColor)
			SDL_SetRenderDrawColor(getWindow()->getSDL_Renderer(), 255, 0, 0, 255);

		SDL_RenderDrawRect(getWindow()->getSDL_Renderer(), &scaled);

		if (defaultColor)
			SDL_SetRenderDrawColor(getWindow()->getSDL_Renderer(), 255, 255, 255, 255);
	}

	//move that amount left or right
	void move(int _x, int _y)
	{
		setPosition(getRect()->x + _x, getRect()->y + _y);
	}

	void setTexture(SoliRom::Asset::Texture _texture)
	{
		texture = _texture.get();
	}
protected:

	std::chrono::milliseconds frameTime = std::chrono::milliseconds(200);
	std::chrono::steady_clock::time_point timeLastFrame = std::chrono::steady_clock::now() - frameTime;
	std::chrono::steady_clock::time_point timeNow;
	int frame = 1;
};

class chip : public things
{
public:
	chip()
	{
		sizeMul = 1;
		setSize(100 * sizeMul, 100 * sizeMul);
		setPosition(-10000, -10000); //off screen so its invis

		reScale();
	}

	bool used = false;

	static void loadAssets()
	{
		chip1.create("Assets/chip_1.png", getWindow());
		chip2.create("Assets/chip_2.png", getWindow());
		chip3.create("Assets/chip_3.png", getWindow());
	};


	void animate()
	{
		timeNow = std::chrono::steady_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(timeNow.time_since_epoch() - timeLastFrame.time_since_epoch()) > frameTime)
		{
			switch (frame)
			{
			case 1:
				setTexture(chip1);
				break;
			case 2:
				setTexture(chip2);
				break;
			case 3:
				setTexture(chip3);
				frame = 0;
				break;
			}
			timeLastFrame = std::chrono::steady_clock::now();
			frame++;
		}
	}

	static int heldChip;

private:

	static SoliRom::Asset::Texture chip1;
	static SoliRom::Asset::Texture chip2;
	static SoliRom::Asset::Texture chip3;
};

class Guy : public things
{
private:

	//weedguy idle
	SoliRom::Asset::Texture Idle1;
	SoliRom::Asset::Texture Idle2;
	SoliRom::Asset::Texture Idle3;
	//weedguy booger
	SoliRom::Asset::Texture Pick1;
	SoliRom::Asset::Texture Pick2;
	//weedguy wants dorito
	SoliRom::Asset::Texture Hungry1;
	SoliRom::Asset::Texture Hungry2;
	//smoke
	SoliRom::Asset::Texture Smoke1;
	SoliRom::Asset::Texture Smoke2;
	//fuck
	SoliRom::Asset::Texture Fuck1;
	SoliRom::Asset::Texture Fuck2;

	int loopcount = 0;

	bool animationComplete = false;
public:

	enum animation
	{
		IDLE, BOOGER, HUNGRY, FUCK, BOOF, ENDOFLIST
	};

	animation currentAnimation = IDLE;
	animation nextAnimation = ENDOFLIST;

	Guy();

	void idle()
	{
		timeNow = std::chrono::steady_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(timeNow.time_since_epoch() - timeLastFrame.time_since_epoch()) > frameTime)
		{
			switch (frame)
			{
			case 1:
				setTexture(Idle1);
				break;
			case 2:
				setTexture(Idle2);
				break;
			case 3:
				setTexture(Idle3);
				animationComplete = true;
				break;
			}
			timeLastFrame = std::chrono::steady_clock::now();
			frame++;
		}
	}

	void booger()
	{
		timeNow = std::chrono::steady_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(timeNow.time_since_epoch() - timeLastFrame.time_since_epoch()) > frameTime)
		{
			switch (frame)
			{
			case 1:
				setTexture(Pick1);
				break;
			case 2:
				setTexture(Pick2);
				loopcount++;
				frame = 0;
				if (loopcount > 2)
				{
					animationComplete = true;
				}
			default:
				break;
			}
			timeLastFrame = std::chrono::steady_clock::now();
			frame++;
		}
	}

	void hungry()
	{

		timeNow = std::chrono::steady_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(timeNow.time_since_epoch() - timeLastFrame.time_since_epoch()) > frameTime)
		{
			switch (frame)
			{
			case 1:
				setTexture(Hungry1);
				break;
			case 2:
				setTexture(Hungry2);
			default:
				animationComplete = true;
				break;
			}
			timeLastFrame = std::chrono::steady_clock::now();
			frame++;
		}
	}

	void fuck()
	{
		timeNow = std::chrono::steady_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(timeNow.time_since_epoch() - timeLastFrame.time_since_epoch()) > frameTime)
		{
			switch (frame)
			{
			case 1:
				setTexture(Fuck1);
				break;
			case 2:
				setTexture(Fuck2);
			default:
				animationComplete = true;
				break;
			}
			timeLastFrame = std::chrono::steady_clock::now();
			frame++;
		}
	}

	bool blowSmoke = false;
	void boof()
	{

		timeNow = std::chrono::steady_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(timeNow.time_since_epoch() - timeLastFrame.time_since_epoch()) > frameTime)
		{
			switch (frame)
			{
			case 1:
				setTexture(Smoke1);
				break;
			case 2:
				setTexture(Smoke2);
			default:
				loopcount++;
				frame = 0;
				if (loopcount > 5)
				{
					animationComplete = true;
					blowSmoke = true;
				}
				break;
			}
			timeLastFrame = std::chrono::steady_clock::now();
			frame++;
		}
	}

	bool fullAnimation = true;
	bool skip = false;

	void setAnimation(animation _setAnim, bool _interupt, bool _fullAnimation)
	{
		fullAnimation = _fullAnimation;

		if (!fullAnimation)
		{
			skip = false;
		}


		if (nextAnimation == ENDOFLIST && currentAnimation != _setAnim)
		{
			nextAnimation = _setAnim;
		}

		if (_interupt && currentAnimation != _setAnim)
		{
			nextAnimation = _setAnim;
			animationComplete = true;
		}
	}

	void animate()
	{
		if (animationComplete || skip)
		{
			skip = false;
			animationComplete = false;
			loopcount = 0;
			frame = 1;

			if (nextAnimation == ENDOFLIST)
			{
				currentAnimation = IDLE;
			}
			else
			{
				currentAnimation = nextAnimation;
				nextAnimation = ENDOFLIST;
			}
		}

		switch (currentAnimation)
		{
		case IDLE:
			idle();
			break;
		case BOOGER:
			booger();
			break;
		case HUNGRY:
			hungry();
			break;
		case FUCK:
			fuck();
			break;
		case BOOF:
			boof();
			break;
		default:
			break;
		}

		if (!fullAnimation)
		{
			skip = true;
			fullAnimation = true;
		}
	}
};

class Boof : public things
{
public:
	SoliRom::Asset::Texture boof;

	Boof()
	{
		boof.create("Assets/jont.png", getWindow());
		setTexture(boof);
		setSize(450 / 2, 250 / 2);
	}

	bool held = false;

	bool jointLogic(Guy* _weedguy)
	{

		//IF JOINT CLICKED

		if (SoliRom::EventHandler::click())
		{
			if (SoliRom::EventHandler::mouseInObj(this))
			{
				held = true;
			}
		}

		if (held)
		{
			setPosition((SoliRom::EventHandler::getMouse().x * (1 / scale)) - (getRect()->w / 2), (SoliRom::EventHandler::getMouse().y * (1 / scale)) - (getRect()->h / 2));

			if (SoliRom::EventHandler::getMouse().state != SoliRom::MouseState::HELD && !SoliRom::EventHandler::click())
			{
				held = false;
				setPosition(0, 0);

				if (SoliRom::EventHandler::mouseInObj(_weedguy))
				{
					//smoke joint
					return true;
				}
			}
		}


		return false;
	}

	int skækness = 90000;

};

class Knife : public things
{
public:
	bool held = false;

	Knife()
	{
		std::string load;
		for (int i = 0; i < 10; i++)
		{
			load = "Assets/KNIFE" + std::to_string(i + 1) + ".png";
			knives[i].create(load, getWindow());
		}
		frameTime = std::chrono::milliseconds(200);
		frame = 0;
		sizeMul = 3;
		setSize(30 * sizeMul, 78 * sizeMul);
		setPosition(getWindow()->getWidth() - getRect()->w, (int)(getWindow()->getHeight() / 1.5) - (getRect()->h / 2));
		//size 30 78
	}
	SoliRom::Asset::Texture knives[10];

	void animate()
	{
		timeNow = std::chrono::steady_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(timeNow.time_since_epoch() - timeLastFrame.time_since_epoch()) > frameTime)
		{
			setTexture(knives[frame]);
			if (frame == 9)
			{
				frame = -1;
			}
			timeLastFrame = std::chrono::steady_clock::now();
			frame++;
		}
	}

	bool knifeLogic(Guy* _weedguy)
	{
		//IF KNIFE CLICKED
		if (SoliRom::EventHandler::click())
		{
			if (SoliRom::EventHandler::mouseInObj(this))
			{
				held = true;
			}
		}

		if (held)
		{
			setPosition((SoliRom::EventHandler::getMouse().x * (1 / scale)) - (getRect()->w / 2), (SoliRom::EventHandler::getMouse().y * (1 / scale)) - (getRect()->h / 2));

			if (SoliRom::EventHandler::getMouse().state != SoliRom::MouseState::HELD && !SoliRom::EventHandler::click())
			{
				held = false;
				setPosition(getWindow()->getWidth() - getRect()->w, (int)(getWindow()->getHeight() / 1.5) - (getRect()->h / 2));

				if (SoliRom::EventHandler::mouseInObj(_weedguy))
				{
					//kill the guy liksom
					setPosition(-1000, -1000);
					return true;
				}
			}
		}
		return false;
	}

};

class exhale : public things
{
public:
	exhale(Guy* _weedGuy)
	{
		std::string load;
		for (int i = 0; i < 12; i++)
		{
			load = "Assets/smoke" + std::to_string(i + 1) + ".png";
			smokes[i].create(load, getWindow());
		}
		frameTime = std::chrono::milliseconds(200);
		frame = 0;
		sizeMul = 2;
		setSize(300, 300);
		setPosition(_weedGuy->getRect()->x + (_weedGuy->getRect()->w / 2.8), _weedGuy->getRect()->y + (_weedGuy->getRect()->h / 1.6) - getRect()->h);
		//size 30 78
	}
	SoliRom::Asset::Texture smokes[12];

	bool done = true;

	bool animate()
	{
		if (done && frame == 0)
		{
			done = false;
		}

		timeNow = std::chrono::steady_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(timeNow.time_since_epoch() - timeLastFrame.time_since_epoch()) > frameTime)
		{
			setTexture(smokes[frame]);
			if (frame == 9)
			{
				done = true;
				frame = -1;
			}
			timeLastFrame = std::chrono::steady_clock::now();
			frame++;
		}

		return done;
	}
};