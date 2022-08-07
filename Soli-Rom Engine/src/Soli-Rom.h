#pragma once

#include "Engine/App.h"
#include "Engine/Windows/Window.h"
#include "Engine/Log.h"
#include "Engine/Engine Objects/GameObject.h"
#include "Engine/Assets/Asset.h"
#include "Engine/Input.h"

//Entry Point
int main(int argc, char* args[])
{
	SoliRom::Log::Init();

	auto program = SoliRom::App::CreateApp();

	program->Run();

	delete program;

	return 0;
}