#include "Framework.h"

#include "Scenes/TutorialScene.h"
#include "Scenes/SolaSystemScene.h"
#include "Scenes/SphereScene.h"
#include "Scenes/GridScene.h"
#include "Scenes/SpawnScene.h"
#include "Scenes/CollisionScene.h"
#include "Scenes/ShootingScene.h"
#include "Scenes/MineCraftScene.h"
#include "Scenes/LightScene.h"
#include "Scenes/TerrainScene.h"
#include "Scenes/CubeMapEditorScene.h"
#include "Scenes/PacmanScene.h"
#include "Scenes/ModelRenderScene.h"
#include "Scenes/ModelExportScene.h"
#include "Scenes/InstancingScene.h"
#include "Scenes/ModelInstancingScene.h"
#include "Scenes/ModelAnimationScene.h"
#include "Scenes/ModelEquipScene.h"
#include "Scenes/MapEditorScene.h"
#include "Scenes/AStarScene.h"
#include "Scenes/RenderTargetScene.h"
#include "Scenes/OutlineScene.h"
#include "Scenes/WaterScene.h"
#include "Scenes/BillboardScene.h"
#include "Scenes/WeatherScene.h"
#include "Scenes/ParticleEditorScene.h"
#include "Scenes/ShadowScene.h"
#include "Scenes/ModelAnimationInstancingScene.h"
#include "Scenes/TessellationScene.h"
#include "Scenes/TerrainLODScene.h"
#include "Scenes/TrailScene.h"

GameManager::GameManager()
{
	SCENE->Create("Grid", new GridScene());
	//SCENE->Create("Export", new ModelExportScene());
	//SCENE->Create("Start", new SphereScene());
	//SCENE->Create("Start", new SpawnScene());
	//SCENE->Create("Start", new CollisionScene());
	//SCENE->Create("Start", new ShootingScene());
	SCENE->Create("Start", new MineCraftScene());
	//SCENE->Create("Start", new LightScene());
	//SCENE->Create("Start", new TerrainScene());
	//SCENE->Create("Start", new CubeMapEditorScene());
	//SCENE->Create("Start", new PacmanScene());	
	//SCENE->Create("Start", new ModelRenderScene());
	//SCENE->Create("Start", new InstancingScene());
	//SCENE->Create("Start", new ModelInstancingScene());
	//SCENE->Create("Start", new ModelAnimationScene());
	//SCENE->Create("Start", new ModelEquipScene());
	//SCENE->Create("Start", new MapEditorScene());
	//SCENE->Create("Start", new AStarScene());
	//SCENE->Create("Start", new RenderTargetScene());
	//SCENE->Create("Start", new OutlineScene());	
	//SCENE->Create("Start", new WaterScene());	
	//SCENE->Create("Start", new BillboardScene());	
	//SCENE->Create("Start", new WeatherScene());	
	//SCENE->Create("Start", new ParticleEditorScene());	
	//SCENE->Create("Start", new ShadowScene());	
	//SCENE->Create("Start", new ModelAnimationInstancingScene());
	//SCENE->Create("Start", new TessellationScene());
	//SCENE->Create("Start", new TerrainLODScene());
	//SCENE->Create("Start", new TrailScene());

	//SCENE->Add("Grid");
	SCENE->Add("Start");

	Create();
}

GameManager::~GameManager()
{
	Release();
}

void GameManager::Update()
{
	Keyboard::Get()->Update();
	Timer::Get()->Update();
	Audio::Get()->Update();

	SCENE->Update();

	Environment::Get()->Update();
}

void GameManager::Render()
{
	SCENE->PreRender();

	Device::Get()->Clear();

	Environment::Get()->SetRender();
	Environment::Get()->SetViewport();
	SCENE->Render();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Font::Get()->GetDC()->BeginDraw();

	string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
	Font::Get()->RenderText(fps, { 100, SCREEN_HEIGHT - 10 });

	Environment::Get()->SetPostRender();
	SCENE->PostRender();

	Environment::Get()->Edit();
	SCENE->GUIRender();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Font::Get()->GetDC()->EndDraw();

	Device::Get()->Present();
}

void GameManager::Create()
{
	Device::Get();
	Environment::Get();
	Timer::Get();
	Keyboard::Get();
	SceneManager::Get();
	Font::Get();
	Observer::Get();
	Audio::Get();

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);

	Font::Get()->AddColor("White", 1, 1, 1);
	Font::Get()->AddStyle("Default", L"����ü");

	Font::Get()->SetColor("White");
	Font::Get()->SetStyle("Default");
}

void GameManager::Release()
{
	Device::Delete();	
	Environment::Delete();
	Timer::Delete();
	Keyboard::Delete();
	SceneManager::Delete();
	Font::Delete();
	Observer::Delete();
	Audio::Delete();

	Shader::Delete();
	Texture::Delete();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	ImGui::DestroyContext();
}

