#include "Engine/App.h"
#include "Engine/Log.h"

//Entry Point
int main(int argc, char* args[])
{
	SoliRom::Log::Init();

	auto program = SoliRom::App::CreateApp();

	program->Run();

	delete program;

	return 0;
}