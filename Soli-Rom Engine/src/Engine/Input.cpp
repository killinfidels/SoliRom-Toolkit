#include "precompiledheaders.h"
#include "Input.h"
#include "Log.h"

namespace SoliRom
{
	Mouse EventHandler::mouse = {0, 0, IDLE};
	SDL_Event EventHandler::e;
	std::vector<EventHandler::Key> EventHandler::keyboard;
	bool EventHandler::quit = false;

	void EventHandler::update()
	{
		//reset click and set held
		if (mouse.click == true)
		{
			mouse.click = false;
			//if its not actually held it will be reset by mousebutton up
			mouse.state = HELD;
		}

		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_MOUSEMOTION:
				mouse.x = e.motion.x;
				mouse.y = e.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouse.click = true;
				break;
			case SDL_MOUSEBUTTONUP:
				mouse.state = IDLE;
				break;
			case SDL_KEYDOWN:
				for (int i = 0; i <= keyboard.size(); i++)
				{
					//create new entry for key if not found
					if (i != keyboard.size() - 1)
					{
						keyboard.resize(keyboard.size() + 1);
						keyboard[i].keyID = e.key.keysym.sym;
					}

					//set key state
					if (keyboard[i].keyID == e.key.keysym.sym)
					{
						keyboard[i].keyState = true;
						i = keyboard.size() + 1;
					}
				}
				break;
			case SDL_KEYUP:
				for (int i = 0; i <= keyboard.size(); i++)
				{
					//set key state false
					if (keyboard[i].keyID == e.key.keysym.sym)
					{
						keyboard[i].keyState = false;
						i = keyboard.size() + 1;
					}
				}
				break;
			case SDL_WINDOWEVENT:
				//temp
				if (e.window.event == SDL_WINDOWEVENT_CLOSE)
					quit = true;
				break;
			default:
				break;
			}
		}
	}


	Mouse EventHandler::getMouse()
	{
		return mouse;
	}

	bool EventHandler::getQuit()
	{
		return quit;
	}
}