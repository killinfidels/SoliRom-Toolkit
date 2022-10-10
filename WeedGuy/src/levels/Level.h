#pragma once

class Level
{
public:
	enum LevelId
	{
		Menu,
		ShackExt,
		ShackInt,
		CaveExt,
		CaveInt,
		ENDOFLIST
	};

	virtual void Load(LevelId _previousLevel) {}
	virtual void Script() {}
	virtual void Draw() {}
	virtual void Quit() {}

	virtual LevelId LevelTransition() { return levelIdentification; }
	LevelId GetId() { return levelIdentification; };


	//returns true if level has loaded
	bool Loaded() { return loadSuccess; };

	~Level() {}
protected:
	SoliRom::Window* w_game;
	SoliRom::App* app;
	SoliRom::AssetManager* assetManager;
	bool loadSuccess = false;
	Level()
	{
		app = SoliRom::App::Get();
		w_game = app->GetCurrentWindow();
		assetManager = SoliRom::AssetManager::Get();
		//assetManager->setWindow(w_game);

		levelIdentification = LevelId::ENDOFLIST;
	};

	LevelId levelIdentification;
	//returns string of scene to switch to
};

