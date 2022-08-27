#pragma once
#include "precompiledheaders.h"

namespace SoliRom
{
	//Mouse Actions
	enum MouseState
	{
		HELD,
		IDLE
	};
	//Mouse state
	struct Mouse
	{
		int x, y;
		bool click = false;
		MouseState state = IDLE;
	};
	//key state

	class EventHandler
	{
	public:


		static void update();

		static Mouse getMouse();
		static bool getQuit();
		static bool keyPressed(int _keyCode);


	private:
		EventHandler();
		//keyboardstate
		static struct Key
		{
			int keyID;
			bool keyState;
		};
		static std::vector<Key> keyboard;
		//mousestate
		static Mouse mouse;
		static SDL_Event e;
		//window events
		static bool quit; //temp
	};
}