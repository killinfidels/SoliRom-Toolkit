#include "Soli-Rom.h"

SoliRom::App TestSpace(3);


class things : public SoliRom::GameObject
{
private:

public:
	SDL_Texture* texture;
	void draw()
	{
		SDL_RenderCopy(TestSpace.getWindow()->getRenderer(), texture, NULL, getRect());
	}

	float sizeMul = 1;

	//move that amount left or right
	void move(int _x, int _y)
	{
		setPosition(getRect()->x + _x, getRect()->y + _y);
	}

	void setTexture(SoliRom::Asset _texture)
	{
		texture = _texture.getTexture();
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
	}

	bool used = false;

	static void loadAssets()
	{
		chip1.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "Assets/chip_1.png");
		chip2.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "Assets/chip_2.png");
		chip3.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "Assets/chip_3.png");
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

	static SoliRom::Asset chip1;
	static SoliRom::Asset chip2;
	static SoliRom::Asset chip3;
};

 SoliRom::Asset chip::chip1;
 SoliRom::Asset chip::chip2;
 SoliRom::Asset chip::chip3;

 int chip::heldChip = -1;

 class guy : public things
 {
 private:

	 //weedguy idle
	 SoliRom::Asset Idle1;
	 SoliRom::Asset Idle2;
	 SoliRom::Asset Idle3;
	 //weedguy booger
	 SoliRom::Asset Pick1;
	 SoliRom::Asset Pick2;
	 //weedguy wants dorito
	 SoliRom::Asset Hungry1;
	 SoliRom::Asset Hungry2;
	 //smoke
	 SoliRom::Asset Smoke1;
	 SoliRom::Asset Smoke2;
	 //fuck
	 SoliRom::Asset Fuck1;
	 SoliRom::Asset Fuck2;

	 int loopcount = 0;
 public:
	 void FLIPdraw()
	 {
		 SDL_RenderCopyEx(TestSpace.getWindow()->getRenderer(), texture, NULL, getRect(), 0, NULL, SDL_FLIP_VERTICAL);
	 }

	 enum animation
	 {
		 IDLE, BOOGER, HUNGRY, FUCK, BOOF
	 };

	 animation currentAnimation = IDLE;

	 guy()
	 {
		 sizeMul = 4;
		 setSize(100 * sizeMul, 100 * sizeMul);
		 setPosition(TestSpace.getWindow()->getWindowWidth() - getRect()->w, (int)(TestSpace.getWindow()->getWindowHeight() / 1.5) - (getRect()->h / 2));
		 
		 Idle1.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "Assets/idle_1.png");
		 Idle2.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "Assets/idle_2.png");
		 Idle3.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "Assets/idle_3.png");
		 Pick1.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "Assets/nosepick_1.png");
		 Pick2.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "Assets/nosepick_1.png");
		 Hungry1.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "Assets/food_1.png");
		 Hungry2.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "Assets/food_2.png");
		 Smoke1.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "Assets/smoke_1.png");
		 Smoke2.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "Assets/smoke_2.png");
		 Fuck1.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "Assets/fuck_1.png");
		 Fuck2.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "Assets/fuck_2.png");
	 }

	 void idle()
	 {
		 if (currentAnimation != IDLE)
		 {
			 frame = 1;
			 currentAnimation = IDLE;
		 }

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
				 frame = 0;
				 break;
			 }
			 timeLastFrame = std::chrono::steady_clock::now();
			 frame++;
		 }
	 }

	 void booger()
	 {
		 if (currentAnimation != BOOGER)
		 {
			 frame = 1;
			 currentAnimation = BOOGER;
			 loopcount = 0;
		 }

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
			 default:
				 break;
			 }
			 timeLastFrame = std::chrono::steady_clock::now();
			 frame++;
		 }
	 }

	 void hungry()
	 {
		 if (currentAnimation != HUNGRY)
		 {
			 frame = 1;
			 currentAnimation = HUNGRY;
		 }

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
				 frame = 0;
				 break;
			 }
			 timeLastFrame = std::chrono::steady_clock::now();
			 frame++;
		 }
	 }

	 void fuck()
	 {
		 if (currentAnimation != FUCK)
		 {
			 frame = 1;
			 currentAnimation = FUCK;
		 }

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
				 frame = 0;
				 break;
			 }
			 timeLastFrame = std::chrono::steady_clock::now();
			 frame++;
		 }
	 }

	 void boof()
	 {
		 if (currentAnimation != BOOF)
		 {
			 frame = 1;
			 currentAnimation = BOOF;
			 loopcount = 0;
		 }

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
				 frame = 0;
				 loopcount++;
				 break;
			 }
			 timeLastFrame = std::chrono::steady_clock::now();
			 frame++;
		 }
	 }

	 bool blowsmoke = false;

	 void animate(animation _setAnim)
	 {
		 if (_setAnim == FUCK || currentAnimation == FUCK)
		 {
			 fuck();
		 }
		 else
		 {
		 if (loopcount < 5 && currentAnimation == BOOF)
		 {
			 boof();
			 if (loopcount == 5)
			 {
				 blowsmoke = true;
			 }
		 }
		 else
		 {
			 if (loopcount < 2 && currentAnimation == BOOGER)
			 {
				 booger();
			 }
			 else
			 {
				 loopcount = 0;
				 switch (_setAnim)
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
			 }
		 }
		 }
	 }
 };

 class boof : public things
 {
 public:
	 SoliRom::Asset Boof;

	 boof()
	 {
		 Boof.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "Assets/jont.png");
		 setTexture(Boof);
		 setSize(450 / 2, 250 / 2);
	 }

	 bool held = false;

	 bool jointLogic(guy* _weedguy)
	 {

			 //IF JOINT CLICKED
			 if (SoliRom::EventHandler::getMouseX() > getRect()->x && SoliRom::EventHandler::getMouseX() < getRect()->x + getRect()->w)
			 {
				 if (SoliRom::EventHandler::getMouseY() > getRect()->y && SoliRom::EventHandler::getMouseY() < getRect()->y + getRect()->h)
				 {

					 if (SoliRom::EventHandler::getMouseState() != SoliRom::MouseCondition::HELD)
					 {
						 held = false;
					 }
					 if (SoliRom::EventHandler::getMouseState() == SoliRom::MouseCondition::CLICKED)
					 {
						 held = true;
					 }

					 if (held)
					 {
						 setPosition(SoliRom::EventHandler::getMouseX() - (getRect()->w / 2), SoliRom::EventHandler::getMouseY() - (getRect()->h / 2));
					 }
					 else
					 {
						setPosition(0, 0);
						 if (SoliRom::EventHandler::getMouseX() > _weedguy->getRect()->x && SoliRom::EventHandler::getMouseX() < _weedguy->getRect()->x + _weedguy->getRect()->w)
						 {
							 if (SoliRom::EventHandler::getMouseY() > _weedguy->getRect()->y && SoliRom::EventHandler::getMouseY() < _weedguy->getRect()->y + _weedguy->getRect()->h)
							 {
								 //smoke joint
								 return true;
							 }
						 }

					 }
				 }
			 }

			 return false;
	 }

	 int skækness = 90000;

 };

 class knife : public things
 {
 public:
	 bool held = false;

	 knife()
	 {
		 std::string load;
		 for (int i = 0; i < 10; i++)
		 {
			 load = "Assets/KNIFE" + std::to_string(i + 1) + ".png";
			 knives[i].createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, load);
		 }
		 frameTime = std::chrono::milliseconds(200);
		 frame = 0;
		 sizeMul = 2;
		 setSize(30 * sizeMul, 78 * sizeMul);
		 setPosition(TestSpace.getWindow()->getWindowWidth() - getRect()->w, 0);
		 //size 30 78
	 }
	 SoliRom::Asset knives[10];

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

	 bool knifeLogic(guy* _weedguy)
	 {
		 //IF JOINT CLICKED
		 if (SoliRom::EventHandler::getMouseX() > getRect()->x && SoliRom::EventHandler::getMouseX() < getRect()->x + getRect()->w)
		 {
			 if (SoliRom::EventHandler::getMouseY() > getRect()->y && SoliRom::EventHandler::getMouseY() < getRect()->y + getRect()->h)
			 {

				 if (SoliRom::EventHandler::getMouseState() != SoliRom::MouseCondition::HELD)
				 {
					 held = false;
				 }
				 if (SoliRom::EventHandler::getMouseState() == SoliRom::MouseCondition::CLICKED)
				 {
					 held = true;
				 }

				 if (held)
				 {
					 setPosition(SoliRom::EventHandler::getMouseX() - (getRect()->w / 2), SoliRom::EventHandler::getMouseY() - (getRect()->h / 2));
				 }
				 else
				 {
					 setPosition(TestSpace.getWindow()->getWindowWidth() - getRect()->w, 0);
					 if (SoliRom::EventHandler::getMouseX() > _weedguy->getRect()->x && SoliRom::EventHandler::getMouseX() < _weedguy->getRect()->x + _weedguy->getRect()->w)
					 {
						 if (SoliRom::EventHandler::getMouseY() > _weedguy->getRect()->y && SoliRom::EventHandler::getMouseY() < _weedguy->getRect()->y + _weedguy->getRect()->h)
						 {
							 //smoke joint
							 return true;
						 }
					 }

				 }
			 }
		 }

		 return false;
	 }

 };

 class exhale : public things
 {
 public:
	 exhale(guy* _weedGuy)
	 {
		 std::string load;
		 for (int i = 0; i < 12; i++)
		 {
			 load = "Assets/smoke" + std::to_string(i + 1) + ".png";
			 smokes[i].createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, load);
		 }
		 frameTime = std::chrono::milliseconds(200);
		 frame = 0;
		 sizeMul = 2;
		 setSize(300, 300);
		 setPosition(_weedGuy->getRect()->x + (_weedGuy->getRect()->w / 2.8), _weedGuy->getRect()->y + (_weedGuy->getRect()->h / 1.6) - getRect()->h);
		 //size 30 78
	 }
	 SoliRom::Asset smokes[12];

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