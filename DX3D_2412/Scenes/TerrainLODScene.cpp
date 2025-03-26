#include "Framework.h"
#include "TerrainLODScene.h"

TerrainLODScene::TerrainLODScene()
{
	terrain = new TerrainLOD(L"Resources/Textures/HeightMaps/PackMan.png");
}

TerrainLODScene::~TerrainLODScene()
{
	delete terrain;
}

void TerrainLODScene::Update()
{
}

void TerrainLODScene::PreRender()
{
}

void TerrainLODScene::Render()
{
	terrain->Render();
}

void TerrainLODScene::PostRender()
{
}

void TerrainLODScene::GUIRender()
{
	terrain->GUIRender();
}
