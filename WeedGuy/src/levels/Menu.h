#include "../core.h"
#include "Level.h"
#include "../objects/Items.h"
#include "../objects/Object.h"

class Menu : public Level
{
	Menu();
	static Menu* instance;

public:
	static Menu* Get();
	~Menu();

	//virtual void Load(LevelId _previousLevel) override;
	//virtual void Script() override;
	//virtual void Draw() override;
	//virtual void Quit() override;
	//virtual LevelId LevelTransition() override;

private:
	SoliRom::Window* w_game;

	enum MenuScreens
	{
		Title, Main, Option
	};

	SoliRom::Asset::Texture* titleTexture;
	SoliRom::Asset::Texture* mainTexture;
	SoliRom::Asset::Texture* optionsTexture;
};