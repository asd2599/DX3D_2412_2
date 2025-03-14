#include "Framework.h"
#include "MineCraftScene.h"

MineCraftScene::MineCraftScene()
{
	BlockManager::Get()->CreateBlocks(10, 10);
	UIManager::Get();

	player = new Player();
	player->SetLocalPosition(5, 5, 5);

	CAM->SetTarget(player);
	CAM->TargetOptionLoad("FPSMode");

	skybox = new Skybox(L"Resources/Textures/Landscape/Snow_ENV.dds");

	renderTarget = new RenderTarget();
	depthStencil = new DepthStencil();

	Texture* texture = Texture::Add(L"Target", renderTarget->GetSRV());
	quad = new Quad(Vector3(SCREEN_WIDTH, SCREEN_HEIGHT));
	quad->GetMaterial()->SetShader(L"PostEffect/Outline.hlsl");
	quad->GetMaterial()->SetDiffuseMap(texture);
	quad->GetMaterial()->GetData()->diffuse = { 0, 1, 0, 1 };
	quad->SetLocalPosition(CENTER);
	quad->UpdateWorld();

	valueBuffer = new FloatValueBuffer();
	valueBuffer->Get()[1] = SCREEN_WIDTH;
	valueBuffer->Get()[2] = SCREEN_HEIGHT;
}

MineCraftScene::~MineCraftScene()
{
	BlockManager::Delete();
	UIManager::Delete();

	delete player;

	delete renderTarget;
	delete depthStencil;

	delete quad;

	delete valueBuffer;
}

void MineCraftScene::Update()
{
	if (KEY->Down(VK_F2))
	{
		CAM->SetTarget(nullptr);
	}

	if (KEY->Down(VK_F3))
	{
		CAM->SetTarget(player);
		CAM->TargetOptionLoad("FPSMode");
	}

	if (KEY->Down(VK_F4))
	{
		CAM->SetTarget(player);
		CAM->TargetOptionLoad("QuaterViewMode");
	}

	BlockManager::Get()->Update();
	UIManager::Get()->Update();

	player->Update();
}

void MineCraftScene::PreRender()
{
	renderTarget->Set(depthStencil);	
	
	UIManager::Get()->RenderSelectBlock();
}

void MineCraftScene::Render()
{
	skybox->Render();
	BlockManager::Get()->Render();
	//player->Render();
}

void MineCraftScene::PostRender()
{
	valueBuffer->SetPS(10);
	quad->Render();

	BlockManager::Get()->PostRender();
	UIManager::Get()->Render();
	player->PostRender();	
}

void MineCraftScene::GUIRender()
{
	ImGui::DragFloat("Value", &valueBuffer->Get()[0]);
	ImGui::DragFloat("Value1", &valueBuffer->Get()[1]);
	ImGui::DragFloat("Value2", &valueBuffer->Get()[2]);

	UIManager::Get()->Edit();
	BlockManager::Get()->Edit();
}
