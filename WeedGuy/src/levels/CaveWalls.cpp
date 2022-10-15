#include "CaveInt.h"


SoliRom::Asset::Texture* CaveWalls::texture = NULL;
Camera3D* CaveWalls::cam = NULL;
SDL_Rect CaveWalls::rect;

CaveWalls::CaveWalls()
{
	visible = true;
}

CaveWalls::~CaveWalls()
{

}

void CaveWalls::LoadTextureAndCamera(std::string _path, Camera3D* _cam)
{
	texture = SoliRom::AssetManager::Get()->createTexture(_path);
	cam = _cam;

	rect =
	{
		-SoliRom::App::Get()->GetCurrentWindow()->getWidth() / 4,
		-SoliRom::App::Get()->GetCurrentWindow()->getHeight() / 4,
		SoliRom::App::Get()->GetCurrentWindow()->getWidth() / 2,
		SoliRom::App::Get()->GetCurrentWindow()->getHeight() / 2
	};
}

void CaveWalls::DrawRect()
{
	rect3D();
	if (visible)
	{
		SDL_RenderDrawRect(texture->GetWindow()->getSDL_Renderer(), &renderRect);
	}
}

void CaveWalls::Draw()
{
	rect3D();
	if (visible)
	{
		SDL_RenderCopy(texture->GetWindow()->getSDL_Renderer(), texture->Get(), NULL, &renderRect);
	}
}

void CaveWalls::rect3D()
{
	int relZ = z - cam->z;

	if (relZ == 0)
		relZ = -1;

	if (relZ < 0)
		visible = false;
	else
		visible = true;

	renderRect.x = (cam->screenDistance * rect.x / relZ) + texture->GetWindow()->getWidth() / 2;
	renderRect.y = (cam->screenDistance * rect.y / relZ) + texture->GetWindow()->getHeight() / 2;
	renderRect.w = (cam->screenDistance * (rect.w) / relZ);// + texture->GetWindow()->getWidth() / 2;
	renderRect.h = (cam->screenDistance * (rect.h) / relZ);// +texture->GetWindow()->getHeight() / 2;
}