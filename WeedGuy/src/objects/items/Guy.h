#pragma once
#include "../../core.h"
#include "../Object.h"

class Guy : public Object
{
private:
	//weedguy idle
	SoliRom::Asset::Animation* a_idle;
	SoliRom::Asset::Animation* a_pick;
	SoliRom::Asset::Animation* a_hungry;
	SoliRom::Asset::Animation* a_smoke;
	SoliRom::Asset::Animation* a_fuck;

	bool animationComplete = false;
public:

	enum animation
	{
		IDLE, BOOGER, HUNGRY, FUCK, BOOF, ENDOFLIST
	};

	animation currentAnimation = IDLE;
	animation nextAnimation = ENDOFLIST;

	Guy();

	bool blowSmoke = false;

	bool fullAnimation = true;
	bool skip = false;

	void setAnimation(animation _setAnim, bool _interupt, bool _fullAnimation);

	void animate();
};