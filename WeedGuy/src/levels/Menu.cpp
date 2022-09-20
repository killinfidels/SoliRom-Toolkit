#include "Menu.h"

Menu* Menu::instance = 0;
Menu* Menu::Get()
{
	if (!instance)
	{
		instance = new Menu;
	}

	return instance;
}

Menu::Menu()
{
	levelIdentification = LevelId::Menu;
}
