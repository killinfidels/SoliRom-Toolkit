#pragma once
#include "precompiledheaders.h"
#include "RectConversions.h"

namespace SoliRom
{
    SDL_FRect RectToFRect(SDL_Rect _rect)
    {
        return SDL_FRect() = {
            (float)_rect.x,
            (float)_rect.y,
            (float)_rect.w,
            (float)_rect.h
        };
    }
    SDL_Rect FRectRound(SDL_FRect _fRect)
    {
        return SDL_Rect() = {
            (int)round(_fRect.x),
            (int)round(_fRect.y),
            (int)round(_fRect.w),
            (int)round(_fRect.h)
        };
    }
}