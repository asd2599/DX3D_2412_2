#include "Framework.h"
#include "AStarScene.h"

AStarScene::AStarScene()
{
	terrain = new Terrain();
	ghost = new Ghost();
	ghost->SetTerrain(terrain);
	aStar = new AStar();
	aStar->SetNode(terrain);
	ghost->SetAStar(aStar);
}

AStarScene::~AStarScene()
{
	delete terrain;
	delete ghost;
	delete aStar;
}

void AStarScene::Update()
{
	ghost->Update();
	aStar->Update();
}

void AStarScene::PreRender()
{
}

void AStarScene::Render()
{
	terrain->Render();
	ghost->Render();
	aStar->Render();
}

void AStarScene::PostRender()
{
}

void AStarScene::GUIRender()
{
	ghost->Edit();
}
