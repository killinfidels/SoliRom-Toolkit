#include "Soli-Rom.h"
#include "Engine/EntryPoint.h"

#include "TestLayer.h"

class TestSpace : public SoliRom::App
{
public:
	TestSpace() : SoliRom::App()
	{
		//w_TestSpace = createWindow("TestSpace :)", 700, 600);
		addLayer(new TestLayer());
	}

private:
	//SoliRom::Window* w_TestSpace;
};

SoliRom::App* SoliRom::App::CreateApp()
{
	return new TestSpace;
}