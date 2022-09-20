#pragma once
#include "../core.h"
#include "Level.h"
#include "../objects/Items.h"
#include "../objects/Object.h"

class ShackExt : public Level
{
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
	SoliRom::Asset::Texture* exterior;
	SoliRom::Asset::Texture* arrow;

	Object level;
	Object door;
	Object left;
	Object right;
};
