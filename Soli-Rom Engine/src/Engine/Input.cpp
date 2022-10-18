#include "precompiledheaders.h"
#include "Input.h"
#include "Log.h"

namespace SoliRom
{
	Mouse Input::mouse;
	SDL_Event Input::e;
	std::vector<Input::Key> Input::keyboard;
	bool Input::quit = false;

	void Input::update()
	{
		//reset Click and set held
		if (mouse.state == CLICKED)
		{
			//if its not actually held it will be reset by mousebutton up
			mouse.state = HELD;
		}

		while (SDL_PollEvent(&e) != 0)
		{
			bool success = false;
			std::string windowName;

			switch (e.type)
			{
			case SDL_MOUSEMOTION:
				mouse.x = e.motion.x;
				mouse.y = e.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouse.state = CLICKED;
				//SR_CORE_WARN("CLICK!");
				windowName = SDL_GetWindowTitle(SDL_GetWindowFromID(e.button.windowID));
				
				mouse.window = App::Get()->GetWindow(windowName);
				break;
			case SDL_MOUSEBUTTONUP:
				mouse.state = IDLE;
				break;
			case SDL_KEYDOWN:
				for (int i = 0; i <= keyboard.size() + 1; i++)
				{
					//set key state
					if (keyboard.size() != 0 && keyboard[i].keyID == e.key.keysym.sym)
					{
						keyboard[i].keyState = true;
						success = true;
						break;
					}
					else if ( i >= (int)keyboard.size() - 1)
					{
						keyboard.resize(keyboard.size() + 1);
						keyboard[keyboard.size() - 1].keyID = e.key.keysym.sym;
						i--;
					}
				}
				break;
			case SDL_KEYUP:
				for (int i = 0; i < keyboard.size(); i++)
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

	bool Input::keyPressed(int _keyID)
	{
		for (int i = 0; i < keyboard.size(); i++)
		{
			if (keyboard[i].keyID == _keyID)
			{
				return keyboard[i].keyState;
			}
		}

		return false;
	}

	Mouse Input::getMouse()
	{
		return mouse;
	}

	bool Input::getQuit()
	{
		return quit;
	}

	bool Input::MouseInRect(SDL_FRect* _rect)
	{
		if (Input::getMouse().x > _rect->x && Input::getMouse().x < _rect->x + _rect->w)
		{
			if (Input::getMouse().y > _rect->y && Input::getMouse().y < _rect->y + _rect->h)
			{
				return true;
			}
		}

		return false;
	}

	bool Input::Click()
	{
		if (mouse.state == CLICKED)
		{
			return true;
		}

		return false;
	}
	bool Input::Held()
	{
		if (mouse.state < 2)
		{
			return true;
		}

		return false;
	}
}