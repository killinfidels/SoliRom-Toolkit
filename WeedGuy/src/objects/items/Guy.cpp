#include "Guy.h"

Guy::Guy()
{
	sizeMul = 4;
	setSize(100 * sizeMul, 100 * sizeMul);
	setPosition(SoliRom::App::Get()->GetCurrentWindow()->getWidth() - GetRect()->w, (int)(SoliRom::App::Get()->GetCurrentWindow()->getHeight() / 1.4) - (GetRect()->h / 2));

	SoliRom::AssetManager* m_temp = SoliRom::AssetManager::Get();

	a_idle = m_temp->createAnimation("assets/idle_1.png");
	a_pick = m_temp->createAnimation("assets/nosepick_1.png");
	a_hungry = m_temp->createAnimation("assets/food_1.png");
	a_smoke = m_temp->createAnimation("assets/smoke_1.png");
	a_fuck = m_temp->createAnimation("assets/fuck_1.png");
}

void Guy::setAnimation(animation _setAnim, bool _interupt, bool _fullAnimation)
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

void Guy::animate()
{
	SoliRom::Asset::Animation* a_currentAnimation;

	if (animationComplete || skip)
	{
		skip = false;
		animationComplete = false;

		if (nextAnimation == ENDOFLIST)
		{
			currentAnimation = IDLE;
		}
		else
		{
			currentAnimation = nextAnimation;
			nextAnimation = ENDOFLIST;
		}

		a_idle->Reset();
		a_pick->Reset();
		a_hungry->Reset();
		a_smoke->Reset();
		a_fuck->Reset();

		a_idle->Stop();
		a_pick->Stop();
		a_hungry->Stop();
		a_smoke->Stop();
		a_fuck->Stop();
	}


	switch (currentAnimation)
	{
	case IDLE:
		a_currentAnimation = a_idle;
		break;
	case BOOGER:
		a_currentAnimation = a_pick;
		break;
	case HUNGRY:
		a_currentAnimation = a_hungry;
		break;
	case FUCK:
		a_currentAnimation = a_fuck;
		break;
	case BOOF:
		a_currentAnimation = a_smoke;
		break;
	default:
		break;
	}

	a_currentAnimation->Start();
	SetTexture(a_currentAnimation->Get());

	switch (currentAnimation)
	{
	case Guy::BOOGER:
		if (a_currentAnimation->Done() > 2)
			animationComplete = true;
		break;
	case Guy::BOOF:
		if (a_currentAnimation->Done() > 5)
		{
			animationComplete = true;
			blowSmoke = true;
		}
		break;
	default:
		if (a_currentAnimation->Done())
			animationComplete = true;
		break;
	}


	if (!fullAnimation)
	{
		skip = true;
		fullAnimation = true;
	}
}