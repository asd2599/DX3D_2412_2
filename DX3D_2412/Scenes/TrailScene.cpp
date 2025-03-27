#include "Framework.h"
#include "TrailScene.h"

TrailScene::TrailScene()
{
	start = new Transform();
	start->SetTag("Start");
	end = new Transform();
	end->SetTag("End");

	sphere = new Sphere();
	
	start->SetParent(sphere);
	end->SetParent(sphere);

	//trail = new Trail(L"Resources/Textures/FX/Trail.png", start, end, 10);
	trail = new Trail(L"Resources/Textures/FX/fire_8x2.png", start, end, 10, 8, 2);
	trail->SetSpeed(10.0f);
}

TrailScene::~TrailScene()
{
	delete start;
	delete end;
	delete sphere;
	delete trail;
}

void TrailScene::Update()
{
	sphere->UpdateWorld();
	start->UpdateWorld();
	end->UpdateWorld();

	trail->Update();
}

void TrailScene::PreRender()
{
}

void TrailScene::Render()
{
	sphere->Render();
	trail->Render();
}

void TrailScene::PostRender()
{
}

void TrailScene::GUIRender()
{
	sphere->Edit();
	start->Edit();
	end->Edit();
}
