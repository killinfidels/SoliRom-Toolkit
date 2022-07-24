#include "Soli-Rom.h"

SoliRom::App TestSpace;


class things : public SoliRom::GameObject
{
private:
	SDL_Texture* texture;

public:
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

protected:
	void setTexture(SoliRom::Asset _texture)
	{
		texture = _texture.getTexture();
	}
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
		chip1.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "../Assets/chip_1.png");
		chip2.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "../Assets/chip_2.png");
		chip3.createAsset(TestSpace.getWindow(), SoliRom::assetType::TEXTURE, "../Assets/chip_3.png");
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
	const std::chrono::milliseconds frameTime = std::chrono::milliseconds(200);
	std::chrono::steady_clock::time_point timeLastFrame = std::chrono::steady_clock::now() - frameTime;
	std::chrono::steady_clock::time_point timeNow;
	int frame = 1;


	static SoliRom::Asset chip1;
	static SoliRom::Asset chip2;
	static SoliRom::Asset chip3;
};

 SoliRom::Asset chip::chip1;
 SoliRom::Asset chip::chip2;
 SoliRom::Asset chip::chip3;

 int chip::heldChip = -1;