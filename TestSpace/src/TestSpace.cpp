#include "TestSpace.h"

class TestSpace : public SoliRom::App
{
public:
	TestSpace() : SoliRom::App()
	{
		w_TestSpace = createWindow("TestSpace :)", 256, 192);
	}

private:
	SoliRom::Window* w_TestSpace;
};

SoliRom::App* SoliRom::App::CreateApp()
{
	return new TestSpace;
}