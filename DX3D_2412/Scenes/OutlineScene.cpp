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

	outlineBuffer = new OutlineBuffer();
	outlineBuffer->Get()[0] = SCREEN_WIDTH;
	outlineBuffer->Get()[1] = SCREEN_HEIGHT;
}

OutlineScene::~OutlineScene()
{
	delete testModel;

	delete renderTarget;
	delete depthStencil;

	delete quad;
	delete outlineBuffer;
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
	outlineBuffer->SetPS(11);
	quad->Render();
}

void OutlineScene::GUIRender()
{
}
