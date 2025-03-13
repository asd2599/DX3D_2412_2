#include "Framework.h"
#include "OutlineScene.h"

OutlineScene::OutlineScene()
{
    testModel = new TestModel();

    renderTarget = new RenderTarget();
    depthStencil = new DepthStencil();

	Texture* texture = Texture::Add(L"Target", renderTarget->GetSRV());
	quad = new Quad(Vector3(SCREEN_WIDTH, SCREEN_HEIGHT));
	quad->GetMaterial()->SetShader(L"PostEffect/Outline.hlsl");
	quad->GetMaterial()->SetDiffuseMap(texture);
	quad->SetLocalPosition(CENTER);
	quad->UpdateWorld();
}

OutlineScene::~OutlineScene()
{
	delete testModel;

	delete renderTarget;
	delete depthStencil;

	delete quad;
}

void OutlineScene::Update()
{
	testModel->Update();
}

void OutlineScene::PreRender()
{
	renderTarget->Set(depthStencil, Float4(0, 0, 0, 0));
	testModel->Render();
}

void OutlineScene::Render()
{
	testModel->Render();
}

void OutlineScene::PostRender()
{	
	quad->Render();
}

void OutlineScene::GUIRender()
{
}
