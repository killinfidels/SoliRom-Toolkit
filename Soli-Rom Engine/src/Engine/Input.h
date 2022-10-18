#pragma once
#include "precompiledheaders.h"
#include "Engine Objects/GameObject.h"
#include "Windows/Window.h"
#include "App.h"

namespace SoliRom
{
	//Mouse Actions
	enum MouseState
	{
		CLICKED,
		HELD,
		IDLE
	};
	//Mouse state
	struct Mouse
	{
		int x, y;
		MouseState state = IDLE;
		Window* window = NULL;
	};
	//key state

	class Input
	{
	public:
		static void update();

		static Mouse getMouse();
		static bool getQuit();
		static bool keyPressed(int _keyCode);


		static bool MouseInRect(SDL_FRect* _rect);
		static bool Click();
		static bool Held();
	private:
		Input();
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