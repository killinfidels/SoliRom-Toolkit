#include "Engine/App.h"
#include "Engine/Log.h"
#include "Engine/Assets/AssetManager.h"

//Entry Point
int main(int argc, char* args[])
{
	SoliRom::Log::Init();

	auto program = SoliRom::CreateApp();

	program->Run();

	delete program;

	return 0;
}