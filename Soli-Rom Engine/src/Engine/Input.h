#pragma once
#include "precompiledheaders.h"

namespace SoliRom
{
	struct MouseState
	{
		int x, y;
		int mouseState;
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

	private:

	};

	EventHandler::EventHandler()
	{
	}

	EventHandler::~EventHandler()
	{
	}
}