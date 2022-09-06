#include "Menu.h"

Menu* Menu::instance = 0;
Menu* Menu::getInstance()
{
	if (!instance)
	{
		instance = new Menu;
	}

	return instance;
}

Menu::Menu()
{
}