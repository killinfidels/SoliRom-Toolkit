#pragma once
#include "core.h"
#include "Level.h"
#include "objects/Items.h"
#include "objects/Object.h"
#include "objects/Player.h"

class ShackExt : public Level
{
private:
	ShackExt();
	static ShackExt* instance;

public:
	static ShackExt* Get();
	~ShackExt();

	virtual void Load(LevelId _previousLevel) override;
	virtual void Script() override;
	virtual void Draw() override;
	//virtual void Quit() override;
	virtual LevelId LevelTransition() override;

private:
	SoliRom::Asset::Texture* t_levelBG;
	SoliRom::Asset::Texture* t_levelFG;
	SoliRom::Asset::Texture* t_arrow;

	Object levelBG;
	Object levelFG;
	Object door;
	Object left;
	Object right;

	std::vector<SDL_FRect> farts;

	float rescale;

	SoliRom::Camera cam;
	
	Player player;

	bool enteringDoorFlag = false;

	SoliRom::Timer loadingTimer;

	int loadingFade = 0;
};
