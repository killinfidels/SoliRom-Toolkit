#pragma once
#include "Soli-Rom.h"
#include <stdio.h>
#include <conio.h>
#include <chrono>
#include <map>

struct Camera
{
	int x, y, w, h;
	float scale;
};

extern Camera cam;