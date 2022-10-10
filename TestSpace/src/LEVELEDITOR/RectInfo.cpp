#include "RectInfo.h"

SoliRom::Asset::Texture* RectInfo::t_x;
SoliRom::Asset::Texture* RectInfo::t_y;
SoliRom::Asset::Texture* RectInfo::t_w;
SoliRom::Asset::Texture* RectInfo::t_h;
SDL_Color RectInfo::black;
SoliRom::AssetManager* RectInfo::am;
int RectInfo::textSize;

RectInfo::RectInfo(int _i, SDL_Rect* _rect)
{
	assignedRect = _rect;
	previous = *assignedRect;
	id = _i;

	//ID BOX
	t_id = am->createTextureFromText(std::to_string(id), textSize, black);
	SDL_QueryTexture(t_id->Get(), NULL, NULL, &g_id.GetRect()->w, &g_id.GetRect()->h);
	g_id.setPosition(0, id * g_id.GetRect()->h * 5);
	g_id.SetTexture(t_id);

	//VALUE INDICATORS
	g_x.SetTexture(t_x);
	g_y.SetTexture(t_y);
	g_w.SetTexture(t_w);
	g_h.SetTexture(t_h);
	SDL_QueryTexture(t_x->Get(), NULL, NULL, &g_x.GetRect()->w, &g_x.GetRect()->h);
	SDL_QueryTexture(t_y->Get(), NULL, NULL, &g_y.GetRect()->w, &g_y.GetRect()->h);
	SDL_QueryTexture(t_w->Get(), NULL, NULL, &g_w.GetRect()->w, &g_w.GetRect()->h);
	SDL_QueryTexture(t_h->Get(), NULL, NULL, &g_h.GetRect()->w, &g_h.GetRect()->h);
	g_x.setPosition(0, g_id.GetRect()->y + g_id.GetRect()->h);
	g_y.setPosition(0, g_x.GetRect()->y + g_x.GetRect()->h);
	g_w.setPosition(0, g_y.GetRect()->y + g_y.GetRect()->h);
	g_h.setPosition(0, g_w.GetRect()->y + g_w.GetRect()->h);

	//VALUES
	t_xValue = am->createTextureFromText(std::to_string(previous.x), textSize, black);
	t_yValue = am->createTextureFromText(std::to_string(previous.y), textSize, black);
	t_wValue = am->createTextureFromText(std::to_string(previous.w), textSize, black);
	t_hValue = am->createTextureFromText(std::to_string(previous.h), textSize, black);
	g_xValue.SetTexture(t_xValue);
	g_yValue.SetTexture(t_yValue);
	g_wValue.SetTexture(t_wValue);
	g_hValue.SetTexture(t_hValue);
	SDL_QueryTexture(t_xValue->Get(), NULL, NULL, &g_xValue.GetRect()->w, &g_xValue.GetRect()->h);
	SDL_QueryTexture(t_yValue->Get(), NULL, NULL, &g_yValue.GetRect()->w, &g_yValue.GetRect()->h);
	SDL_QueryTexture(t_wValue->Get(), NULL, NULL, &g_wValue.GetRect()->w, &g_wValue.GetRect()->h);
	SDL_QueryTexture(t_hValue->Get(), NULL, NULL, &g_hValue.GetRect()->w, &g_hValue.GetRect()->h);
	g_xValue.setPosition(g_x.GetRect()->x + g_x.GetRect()->w, g_x.GetRect()->y);
	g_yValue.setPosition(g_y.GetRect()->x + g_y.GetRect()->w, g_y.GetRect()->y);
	g_wValue.setPosition(g_w.GetRect()->x + g_w.GetRect()->w, g_w.GetRect()->y);
	g_hValue.setPosition(g_h.GetRect()->x + g_h.GetRect()->w, g_h.GetRect()->y);
}

RectInfo::~RectInfo()
{
}

void RectInfo::init()
{
	am = SoliRom::AssetManager::Get();

	black =
	{
		0, 0, 0, 255
	};

	textSize = 28;

	t_x = am->createTextureFromText("X:", textSize, black);
	t_y = am->createTextureFromText("Y:", textSize, black);
	t_w = am->createTextureFromText("W:", textSize, black);
	t_h = am->createTextureFromText("H:", textSize, black);
}

void RectInfo::update()
{

}

void RectInfo::draw()
{
	g_x.Draw();
	g_y.Draw();
	g_w.Draw();
	g_h.Draw();
	g_xValue.Draw();
	g_yValue.Draw();
	g_wValue.Draw();
	g_hValue.Draw();
	g_id.Draw();
}
