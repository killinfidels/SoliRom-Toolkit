#pragma once
#include "core.h"

class Zone
{
public:
	Zone()
	{

	}

	~Zone()
	{

	}

	bool loadSuccess = false;
	bool transition = false;
	bool transitionSuccess = false;

	std::vector<std::string> scene;
	
	int currentScene;

protected:
	void Load();

	void Script();

	//returns string of scene to switch to
	std::string SceneTransition();

	void Draw();
};

