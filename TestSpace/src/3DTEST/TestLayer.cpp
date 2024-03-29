#include "TestLayer.h"

SDL_Renderer* obj_3D::renderer;
SoliRom::Asset::Texture* obj_3D::texture;

TestLayer::TestLayer() : Layer("The Test Layer")
{
	w_3DTest = SoliRom::App::Get()->CreateWindow("WOAH 3D!?!?!?", 700, 600);
	w_2DTest = SoliRom::App::Get()->CreateWindow("TOP DOWN DEBUG!", 700, 600);

	int x, y;
	SDL_GetWindowPosition(w_3DTest->getSDL_Window(), &x, &y);
	SDL_SetWindowPosition(w_3DTest->getSDL_Window(), x - 300, y);
	SDL_SetWindowPosition(w_2DTest->getSDL_Window(), x + 400, y);

	cam.pos.x = 0, cam.pos.y = -200, cam.pos.z = 0;
	cam.middleX = w_3DTest->getWidth() / 2;
	cam.middleY = w_3DTest->getHeight() / 2;
	cam.middleX2 = cam.middleX;
	cam.middleY2 = cam.middleY;
	cam.screenDistance = 400;
	cam.camSpeed = 5;
	cam.xD = 0, cam.yD = 0;

	//3d
	SoliRom::AssetManager::Get()->setWindow(w_3DTest);
	t_tree = SoliRom::AssetManager::Get()->createTexture("assets/Tree.png");
	t_road = SoliRom::AssetManager::Get()->createTexture("assets/Road.png");

	//2d
	SoliRom::AssetManager::Get()->setWindow(w_2DTest);
	t_road2 = SoliRom::AssetManager::Get()->createTexture("assets/Road.png");

	SoliRom::AssetManager::Get()->setWindow(w_3DTest);
	obj_3D::SetTexture(t_tree);
	obj_3D::setRenderer(w_3DTest);
	
	float scale = 1;

	int xSpace = 200 * scale;
	int zSpace = 200 * scale;
	int zRow = 1;
	int size = 300 * scale;

	for (int i = 0; i < 24; i++)
	{
		tree[i].GetRect()->w = size;
		tree[i].GetRect()->h = -size * 2.246543;
		tree[i].UpdateRect();

		tree[i].setZ(zSpace * zRow);
		*tree[i].GetPos() = { (float)-xSpace, 0 };

		if ((i) % 2 != 0)
		{
			*tree[i].GetPos() = { (float)xSpace, 0 };
			zRow++;
		}
	}

	animationTest = SoliRom::AssetManager::Get()->createAnimation("assets/idle_1.png", 200);

	animationTest->Reset();
	animationTest->Start();

	frameTime.Reset();
	frameTime.Start();
}

point TestLayer::pointToScreen(int _x, int _y, int _z)
{
	int relX = _x - cam.pos.x;
	int relY = _y - cam.pos.y;
	int relZ = _z - cam.pos.z;

	//y axis rot
	int rotX = relX * cos(-cam.xD * 3.14159265 / 180) + relZ * sin(-cam.xD * 3.14159265 / 180);
	int rotY = relY;
	int rotZ = relZ * cos(-cam.xD * 3.14159265 / 180) - relX * sin(-cam.xD * 3.14159265 / 180);

	//again but x??
	int NrotX = rotX;
	int NrotY = rotY * cos(-cam.yD * 3.14159265 / 180) - rotZ * sin(-cam.yD * 3.14159265 / 180);
	int NrotZ = rotZ * cos(-cam.yD * 3.14159265 / 180) + rotY * sin(-cam.yD * 3.14159265 / 180);

	if (NrotZ == 0)
		NrotZ = 1;
	
	point screenPoint;
	screenPoint.x = (cam.screenDistance * NrotX / NrotZ) + cam.middleX;
	screenPoint.y = (cam.screenDistance * NrotY / NrotZ) + cam.middleY;
	screenPoint.z = rotZ;

	SDL_RenderDrawPoint(w_2DTest->getSDL_Renderer(), NrotX /5 + cam.middleX2, -NrotZ/5 + cam.middleY2);

	SDL_RenderDrawPoint(w_2DTest->getSDL_Renderer(), screenPoint.x - cam.middleX + cam.middleX2, screenPoint.y - cam.middleY + cam.middleY2);

	return screenPoint;
}

void TestLayer::objSetScreenRect(obj_3D* _obj)
{
	point screenPoint
		= pointToScreen(_obj->GetRect()->x, _obj->GetRect()->y, _obj->getZ());

	point screenPointH = pointToScreen(
		_obj->GetRect()->x,
		_obj->GetRect()->h,
		_obj->getZ());

	//SDL_Rect screenRect
	//{
	//	screenPoint.x - (-screenPointWH.y * 1 / 2.246543) / 2,
	//	screenPoint.y + screenPointWH.y,
	//	screenPoint.y - screenPointWH.y * 1 / 2.246543,
	//	screenPoint.y - screenPointWH.y
	//};

	SDL_Rect screenRect
	{
		screenPoint.x - ((screenPoint.y - screenPointH.y) * 1 / 2.246543) / 2,
		screenPoint.y - (screenPoint.y - screenPointH.y),
		(screenPoint.y - screenPointH.y) * 1 / 2.246543,
		(screenPoint.y - screenPointH.y)
	};

	//screenRect.w = screenRect.h / 2.246543;

	_obj->setRenderRect(screenRect);

	if (screenPoint.z < 0)
		_obj->visible = false;
	else
		_obj->visible = true;
}

void TestLayer::drawRoad()
{
	int z1 = tree[0].getZ();
	int z2 = tree[23].getZ();
	int relz1 = z1 - cam.pos.z;
	int relz2 = z2 - cam.pos.z;

	SDL_Rect roadSize = {
		tree[0].GetRect()->x,
		0,
		tree[1].GetRect()->x - tree[0].GetRect()->x,
		0
	};

	SDL_Rect DrawRect, textureRect;

	for (int i = relz2; i > 0 && i > relz1; i--)
	{
		DrawRect = {
			pointToScreen(roadSize.x, roadSize.y, i + cam.pos.z).x,
			pointToScreen(roadSize.x, roadSize.y, i + cam.pos.z).y,
			pointToScreen(roadSize.x + roadSize.w, roadSize.y, i + cam.pos.z).x - pointToScreen(roadSize.x, roadSize.y, i + cam.pos.z).x,
			1
		};

		int y = pointToScreen(roadSize.x + roadSize.w, roadSize.y, i + cam.pos.z).y - pointToScreen(roadSize.x, roadSize.y, i + cam.pos.z).y;

		SDL_Point size;

		SDL_QueryTexture(t_road->Get(), NULL, NULL, &size.x, &size.y);

		textureRect = {
			0,
			((size.y * (i - relz1 )) / (relz2 - relz1)),
			size.x,
			1
		};

		SDL_Point zero = {
			0, 0
		};

		DrawRect.w = sqrt(y * y + DrawRect.w * DrawRect.w);
		
		//Draw until next liksom
		//for (DrawRect.y; DrawRect.y < pointToScreen(roadSize.x, roadSize.y, i - 1 + cam.pos.z).y; DrawRect.y++)
		{
			SDL_RenderCopyEx(w_3DTest->getSDL_Renderer(), t_road->Get(), &textureRect, &DrawRect, atan2(y,DrawRect.w) * 180 / 3.14159265, &zero, SDL_FLIP_NONE);
		}

	}
}

void TestLayer::draw2D()
{
	for (int i = 0; i < 24; i++)
	{
		//find relative position of trees to camera
		SDL_Rect relative = {
			(tree[i].GetRect()->x + tree[1].GetRect()->w / 2) - 15 - cam.pos.x,
			(-tree[i].getZ() - 15 + cam.pos.z),
			30,
			30
		};

		//rotate
		SDL_Rect rotated = {
			relative.x * cos(-cam.xD * 3.14159265 / 180) - relative.y * sin(-cam.xD * 3.14159265 / 180),
			relative.x * sin(-cam.xD * 3.14159265 / 180) + relative.y * cos(-cam.xD * 3.14159265 / 180),
			relative.w,
			relative.h
		};

		//Move to middle of screen
		rotated.x += cam.middleX2;
		rotated.y += cam.middleY2;

		SDL_RenderDrawPoint(w_2DTest->getSDL_Renderer(), cam.middleX2, cam.middleY2);
		SDL_RenderDrawPoint(w_2DTest->getSDL_Renderer(), cam.pos.x + cam.middleX2 , -cam.pos.z + cam.middleY2*2);
		SDL_RenderFillRect(w_2DTest->getSDL_Renderer(), &rotated);
	}
}

void TestLayer::vertexRender()
{
	int z1 = tree[0].getZ();
	int z2 = tree[23].getZ();
	int relz1 = z1 - cam.pos.z;
	int relz2 = z2 - cam.pos.z;

	SDL_Rect roadSize = {
		tree[0].GetRect()->x,
		0,
		tree[1].GetRect()->x - tree[0].GetRect()->x,
		0
	};

	pointToScreen(roadSize.x, 0, z2);
	pointToScreen(roadSize.x + roadSize.w, 0, z2);

	pointToScreen(roadSize.x, 0, z1);
	pointToScreen(roadSize.x + roadSize.w, 0, z1);
	SDL_Vertex roadVert[6];
	roadVert[0].position = { (float)pointToScreen(roadSize.x, 0, z2).x, (float)pointToScreen(roadSize.x, 0, z2).y };
	roadVert[0].tex_coord = { 0, 0 };
	//roadVert[0].color = { 255, 0, 0, 255 };

	roadVert[1].position = { (float)pointToScreen(roadSize.x, 0, z1).x, (float)pointToScreen(roadSize.x, 0, z1).y };
	roadVert[1].tex_coord = { 0, 1 };
	//roadVert[2].color = { 0, 255, 0, 255 };

	roadVert[2].position = { (float)pointToScreen(roadSize.x + roadSize.w, 0, z2).x, (float)pointToScreen(roadSize.x + roadSize.w, 0, z2).y };
	roadVert[2].tex_coord = { 1, 0 };
	//roadVert[1].color = { 255, 0, 0, 255 };

	roadVert[3].position = { (float)pointToScreen(roadSize.x, 0, z1).x, (float)pointToScreen(roadSize.x, 0, z1).y };
	roadVert[3].tex_coord = { 0, 1 };
	//roadVert[4].color = { 0, 255, 0, 255 };

	roadVert[4].position = { (float)pointToScreen(roadSize.x + roadSize.w, 0, z1).x, (float)pointToScreen(roadSize.x + roadSize.w, 0, z1).y };
	roadVert[4].tex_coord = { 1, 1 };
	//roadVert[5].color = { 0, 255, 0, 255 };

	roadVert[5].position = { (float)pointToScreen(roadSize.x + roadSize.w, 0, z2).x, (float)pointToScreen(roadSize.x + roadSize.w, 0, z2).y };
	roadVert[5].tex_coord = { 1, 0 };
	//roadVert[3].color = { 255, 0, 0, 255 };

	SDL_Vertex vert[3];

	// center
	vert[0].position = { (float)cam.middleX2, (float)cam.middleY2 / 2 };
	vert[0].color = { 255, 0, 0, 255 };
	vert[0].tex_coord = {0.5 , 0};

	// left
	vert[1].position = { (float)cam.middleX2 / 2, (float)cam.middleY2 / 2 * 3 };
	vert[1].color = { 0, 0, 255, 255 };
	vert[1].tex_coord = { 0 , 1 };

	// right 
	vert[2].position = { (float)cam.middleX2 / 2 * 3, (float)cam.middleY2 / 2 * 3};
	vert[2].color = { 0, 255, 0, 255 };
	vert[2].tex_coord = { 1 , 1 };

	//SDL_RenderGeometry(w_2DTest->getSDL_Renderer(), NULL, vert, 3, NULL, 0);

	SDL_RenderGeometry(w_2DTest->getSDL_Renderer(), t_road2->Get(), roadVert, 6, NULL, 0);
	//SDL_Log("%s\n", SDL_GetError());
}

void TestLayer::OnUpdate()
{
	int light = 25;
	//2D WINDOW
	SDL_SetRenderDrawColor(w_2DTest->getSDL_Renderer(), light, light, light, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(w_2DTest->getSDL_Renderer());
	SDL_SetRenderDrawColor(w_2DTest->getSDL_Renderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_GetWindowSize(w_2DTest->getSDL_Window(), &cam.middleX2, &cam.middleY2);

	cam.middleX2 /= 2;
	cam.middleY2 /= 2;

	//3D WINDOW
	SDL_SetRenderDrawColor(w_3DTest->getSDL_Renderer(), light, light, light, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(w_3DTest->getSDL_Renderer());
	SDL_SetRenderDrawColor(w_3DTest->getSDL_Renderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_GetWindowSize(w_3DTest->getSDL_Window(), &cam.middleX, &cam.middleY);

	cam.middleX /= 2;
	cam.middleY /= 2;

	int speedMul = 4;
	int newSpeed = cam.camSpeed;

	if (SoliRom::Input::keyPressed(SDLK_LSHIFT))
		newSpeed *= speedMul;

	//cam pos
	if (SoliRom::Input::keyPressed(SDLK_w))
	{
		cam.pos.x += newSpeed * sin(cam.xD * 3.14159265 / 180);
		cam.pos.z += newSpeed * cos(cam.xD * 3.14159265 / 180);
	}
	if (SoliRom::Input::keyPressed(SDLK_s))
	{
		cam.pos.x -= newSpeed * sin(cam.xD * 3.14159265 / 180);
		cam.pos.z -= newSpeed * cos(cam.xD * 3.14159265 / 180);
	}
	if (SoliRom::Input::keyPressed(SDLK_a))
	{
		cam.pos.x -= newSpeed * cos(cam.xD * 3.14159265 / 180);
		cam.pos.z += newSpeed * sin(cam.xD * 3.14159265 / 180);
	}
	if (SoliRom::Input::keyPressed(SDLK_d))
	{
		cam.pos.x += newSpeed * cos(cam.xD * 3.14159265 / 180);
		cam.pos.z -= newSpeed * sin(cam.xD * 3.14159265 / 180);
	}

	if (SoliRom::Input::keyPressed(SDLK_SPACE))
		cam.pos.y -= newSpeed;
	if (SoliRom::Input::keyPressed(SDLK_LCTRL))
		cam.pos.y += newSpeed;

	//cam angle
	if (SoliRom::Input::keyPressed(SDLK_UP))
		cam.yD += newSpeed / 2;
	if (SoliRom::Input::keyPressed(SDLK_DOWN))
		cam.yD -= newSpeed / 2;
	if (SoliRom::Input::keyPressed(SDLK_RIGHT))
		cam.xD += newSpeed / 2;
	if (SoliRom::Input::keyPressed(SDLK_LEFT))
		cam.xD -= newSpeed / 2;

	if (cam.xD > 180)
		cam.xD -= 360;
	if (cam.xD < -180)
		cam.xD += 360;

	if (cam.yD > 90)
		cam.yD = 90;
	if (cam.yD < -90)
		cam.yD = -90;


	if (SoliRom::Input::keyPressed(SDLK_0) && SoliRom::Input::keyPressed(SDLK_1))
		SR_TRACE("CAN PRESS BOTH");

	drawRoad();

	obj_3D::SetTexture(t_tree);

	for (int i = 0; i < 24; i++)
	{
		objSetScreenRect(&tree[i]);
		//tree[i].DrawRect();
		tree[i].Draw();
	}


	draw2D();

	vertexRender();

	SDL_RenderPresent(w_2DTest->getSDL_Renderer());
	SDL_RenderPresent(w_3DTest->getSDL_Renderer());

	frameTime.update();

	if (SoliRom::Input::keyPressed(SDLK_1) && !pauseOnce)
	{
		//pauseOnce = true;
		frameTime.Stop();
		SR_INFO("TIMER PAUSED");
	}

	if (SoliRom::Input::keyPressed(SDLK_2) && !unpauseOnce)
	{
		//unpauseOnce = true;
		frameTime.Start();
		SR_INFO("TIMER UNPAUSED");
	}

	if (SoliRom::Input::keyPressed(SDLK_3) && !resetOnce)
	{
		//resetOnce = true;
		frameTime.Reset();
		SR_INFO("TIMER RESET");
	}
	
	SR_TRACE("FRAMETIME: %i", (int)(1000 * frameTime.elapsed()));
	printf("\x1B[F");
	frameTime.Reset();


	//SDL_Delay(20);
}
