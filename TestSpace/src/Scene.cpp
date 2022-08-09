#include "Scene.h"

Shack* Shack::instance = 0;

Shack* Shack::getInstance()
{
	if (!instance)
	{
		instance = new Shack;
	}

	return instance;
}