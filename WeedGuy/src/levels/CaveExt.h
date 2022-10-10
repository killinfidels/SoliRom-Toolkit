#pragma once
#include "../core.h"
#include "Level.h"
#include "../objects/Items.h"
#include "../objects/Object.h"

class CaveExt : public Level
{
	CaveExt();
	static CaveExt* instance;

public:
	static CaveExt* Get();
	~CaveExt();

	virtual void Load(LevelId _previousLevel) override;
	virtual void Script() override;
	virtual void Draw() override;
	//virtual void Quit() override;
	virtual LevelId LevelTransition() override;

private:
	SoliRom::Asset::Texture* t_exterior;
	SoliRom::Asset::Texture* t_arrow;
	SoliRom::Asset::Animation* a_entrance;

	Object level;
	Object caveEntrance;
	Object right;
};
