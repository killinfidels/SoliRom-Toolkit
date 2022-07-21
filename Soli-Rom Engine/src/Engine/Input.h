#pragma once
#include "precompiledheaders.h"

namespace SoliRom
{
	enum MouseCondition
	{
		CLICKED,
		IDLE
	};

	struct MouseState
	{
		int x, y;
		MouseCondition mouseState = IDLE;
	};

	struct Key
	{
		int keyID;
		int keyState;
	};

	struct KeyState
	{
		Key keys[];
	};

	class EventHandler
	{
	public:
		EventHandler();
		~EventHandler();

		MouseState mouse;

		void updateMouse();
		int getMouseX();
		int getMouseY();
		MouseCondition getMouseState();


	private:
		SDL_Event e;

	};
}