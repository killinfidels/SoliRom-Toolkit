#include "core.h"

void ScaleRect(SDL_FRect* _rect, float _scale)
{
	_rect->x *= _scale;
	_rect->y *= _scale;
	_rect->w *= _scale;
	_rect->h *= _scale;
}

bool BindToRect(SDL_FRect* _in, SDL_FRect* _out, bool _enforce)
{
	bool flag = false;
	if (_in->x < _out->x)
	{
		flag = true;
		if (_enforce)
			_in->x = _out->x;
	}

	if (_in->y < _out->y)
	{
		flag = true;
		if (_enforce)
			_in->y = _out->y;
	}

	if (_in->x + _in->w > _out->x + _out->w)
	{
		flag = true;
		if (_enforce)
			_in->x = _out->x + _out->w - _in->w;
	}

	if (_in->y + _in->h > _out->y + _out->h)
	{
		flag = true;
		if (_enforce)
			_in->y = _out->y + _out->h - _in->h;
	}
		
	return flag;
}

bool CheckCollision(SDL_FRect* _in, SDL_FRect* _out)
{
	if (_in->x + _in->w > _out->x && _in->x < _out->x + _out->w)
		if (_in->y + _in->h > _out->y && _in->y < _out->y + _out->h)
			return true;

	return false;
}
