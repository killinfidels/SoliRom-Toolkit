#include "precompiledheaders.h"
#include "Input.h"

namespace SoliRom
{
	EventHandler::EventHandler()
	{
	}

	EventHandler::~EventHandler()
	{
	}

	void EventHandler::updateMouse()
	{
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_MOUSEMOTION:
				mouse.x = e.motion.x;
				mouse.y = e.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouse.mouseState = MouseCondition::CLICKED;
				break;
			case SDL_MOUSEBUTTONUP:
				mouse.mouseState = MouseCondition::IDLE;
				break;
			default:
				break;
			}
		}
	}

	int EventHandler::getMouseX()
	{
		return 0;
	}

	int EventHandler::getMouseY()
	{
		return 0;
	}
}