#include "Soli-Rom.h"
#include "Engine/EntryPoint.h"

#include "3DTEST/TestLayer.h"
#include "LEVELEDITOR/CollisionMapper.h"

class TestSpace : public SoliRom::App
{
public:
	TestSpace() : SoliRom::App()
	{
		//w_TestSpace = CreateWindow("TestSpace :)", 700, 600);
		//AddLayer(new TestLayer());
		AddLayer(new CollisionMapper());
	}

private:
	//SoliRom::Window* w_TestSpace;
};

SoliRom::App* SoliRom::CreateApp()
{
	return new TestSpace;
}