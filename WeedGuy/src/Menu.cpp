#include "Menu.h"

Menu* Menu::getInstance()
{
	if (!instance)
	{
		instance = new Menu;
	}

	return instance;
}