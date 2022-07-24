#pragma once
#include "precompiledheaders.h"

namespace SoliRom
{
	enum MouseCondition
	{
		CLICKED,
		HELD,
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
		std::vector<Key> keys;
	};

	class EventHandler
	{
	public:


		static void updateMouse();
		static int getMouseX();
		static int getMouseY();
		static MouseCondition getMouseState();
		static bool getQuit();


	private:
		EventHandler();
		static MouseState mouse;
		static SDL_Event e;
		static bool quit;

	};
}