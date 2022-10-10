#pragma once

#include "Soli-Rom.h"

using namespace SoliRom;

 struct Camera
{
	int x, y, w, h;
	float zoom;
};


extern Camera cam;

enum Allegiance
{
	FRIEND,
	ENEMY,
	NEUTRAL,
	ENDOFLIST
};