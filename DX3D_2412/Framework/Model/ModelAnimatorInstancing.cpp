#include "Framework.h"

ModelAnimatorInstancing::ModelAnimatorInstancing(string name)
    : ModelAnimator(name)
{
    SetShader(L"Instancing/ModelAnimatorInstancing.hlsl");

    instanceBuffer = new VertexBuffer(instanceDatas, sizeof(InstanceData),
        MAX_INSTANCE);
    frameInstancingBuffer = new FrameInstancingBuffer();
}

ModelAnimatorInstancing::~ModelAnimatorInstancing()
{
    delete instanceBuffer;
    delete frameInstancingBuffer;

    for (Transform* transform : transforms)
        delete transform;
}

void ModelAnimatorInstancing::Update()
{
    drawCount = 0;

    FOR(transforms.size())
    {
        if (transforms[i]->IsActive())
        {
            UpdateFrame(&frameInstancingBuffer->GetData()->motions[i]);
            transforms[i]->UpdateWorld();
            instanceDatas[drawCount].world =
                XMMatrixTranspose(transforms[i]->GetWorld());
            instanceDatas[drawCount].index = i;

            drawCount++;
        }
    }

    instanceBuffer->Update(instanceDatas, drawCount);
}

void ModelAnimatorInstancing::Render()
{
    instanceBuffer->Set(1);
    frameInstancingBuffer->SetVS(4);
    DC->VSSetShaderResources(0, 1, &srv);

    for (ModelMesh* mesh : meshes)
        mesh->RenderInstanced(drawCount);
}

void ModelAnimatorInstancing::Edit()
{
    ImGui::Text("DrawCount : %d", drawCount);

    for (Transform* transform : transforms)
        transform->Edit();
}

Transform* ModelAnimatorInstancing::Add()
{
    Transform* transform = new Transform();
    transform->SetTag(name + "_" + to_string(transforms.size()));
    transforms.push_back(transform);

    return transform;
}

void ModelAnimatorInstancing::PlayClip(UINT instanceIndex, int clip, float scale, float takeTime)
{
    ModelClip* modelClip = clips[clip];

    frameInstancingBuffer->GetData()->motions[instanceIndex].next.clip = clip;
    frameInstancingBuffer->GetData()->motions[instanceIndex].next.scale = scale;
    frameInstancingBuffer->GetData()->motions[instanceIndex].duration = takeTime;
    frameInstancingBuffer->GetData()->motions[instanceIndex].runningTime = 0.0f;
    frameInstancingBuffer->GetData()->motions[instanceIndex].playTime
        = modelClip->frameCount / modelClip->tickPerSecond;
}
