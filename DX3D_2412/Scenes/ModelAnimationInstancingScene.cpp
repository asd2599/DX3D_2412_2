#include "Framework.h"
#include "ModelAnimationInstancingScene.h"

ModelAnimationInstancingScene::ModelAnimationInstancingScene()
{
    modelInstancing = new ModelAnimatorInstancing("Agatha");

    FOR(12)
        modelInstancing->ReadClip("Agatha", i);    
    modelInstancing->CreateTexture();

    for (float z = -5.0f; z <= 5.0f; z++)
    {
        for (float x = -5.0f; x <= 5.0f; x++)
        {
            Transform* transform = modelInstancing->Add();
            transform->SetLocalPosition(Vector3(x, 0, z) * 3);
            float scale = 0.001f;
            transform->SetLocalScale(Vector3::One() * scale);
        }
    }
}

ModelAnimationInstancingScene::~ModelAnimationInstancingScene()
{
    delete modelInstancing;
}

void ModelAnimationInstancingScene::Update()
{
    modelInstancing->Update();
}

void ModelAnimationInstancingScene::PreRender()
{    
}

void ModelAnimationInstancingScene::Render()
{
    modelInstancing->Render();
}

void ModelAnimationInstancingScene::PostRender()
{
}

void ModelAnimationInstancingScene::GUIRender()
{
    ImGui::DragInt("Index", &instanceIndex);
    ImGui::DragInt("Clip", &clip);

    if (ImGui::Button("Play"))
        modelInstancing->PlayClip(instanceIndex, clip);

    modelInstancing->Edit();
}
