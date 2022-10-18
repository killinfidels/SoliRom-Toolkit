#include "Exhale.h"

exhale::exhale(Guy* _weedGuy)
{
	int sizeMul = 2;
	SetSize(300, 300);
	SetPos(_weedGuy->GetRect()->x + (_weedGuy->GetRect()->w / 2.8), _weedGuy->GetRect()->y + (_weedGuy->GetRect()->h / 1.6) - GetRect()->h);
	//size 30 78

	a_exhale = SoliRom::AssetManager::Get()->createAnimation("assets/exhale_1.png", 200);
	done = true;

}

bool exhale::animate()
{
	if (done)
	{
		done = false;
		a_exhale->Start();
	}

	if (a_exhale->Done())
	{
		a_exhale->Stop();
		a_exhale->Reset();
		done = true;
	}

	SetTexture(a_exhale->Get());
	return done;
}
