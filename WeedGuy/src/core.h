#pragma once
#include "Soli-Rom.h"
#include <stdio.h>
#include <conio.h>
#include <chrono>
#include <map>

void ScaleRect(SDL_FRect* _rect, float _scale);

bool BindToRect(SDL_FRect* _in, SDL_FRect* _out, bool _enforce);

bool CheckCollision(SDL_FRect* _in, SDL_FRect* _out);