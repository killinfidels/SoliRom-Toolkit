#include "Soli-Rom.h"
#include "Engine/EntryPoint.h"

#include "TestLayer.h"

class TestSpace : public SoliRom::App
{
public:
	TestSpace() : SoliRom::App()
	{
		//w_TestSpace = CreateWindow("TestSpace :)", 700, 600);
		AddLayer(new TestLayer());
	}

private:
	//SoliRom::Window* w_TestSpace;
};

SoliRom::App* SoliRom::CreateApp()
{
	return new TestSpace;
}