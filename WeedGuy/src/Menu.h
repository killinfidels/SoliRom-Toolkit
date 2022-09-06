#include "Zone.h"

class Menu : public Zone

{
public:
	static Menu* getInstance();
	~Menu()
	{

	}

	void Load();

	void Script();

	bool SceneTransition();

	void Draw();

private:
	Menu();
	static Menu* instance;

	enum MenuScreens
	{
		Title, Main, Option
	};
private:
	SoliRom::Texture titleTexture;
	SoliRom::Texture mainTexture;
	SoliRom::Texture optionsTexture;
};