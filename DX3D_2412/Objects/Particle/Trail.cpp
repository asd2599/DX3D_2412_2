#include "Framework.h"

Trail::Trail(wstring imageFile, Transform* start, Transform* end,
    UINT width, float frameX, float frameY, bool isAdditive)
    : start(start), end(end), width(width), isAdditive(isAdditive)
{
    material->SetShader(L"FX/Sprite.hlsl");
    material->SetDiffuseMap(imageFile);

    CreateMesh();

    rasterizerState[0] = new RasterizerState();
    rasterizerState[1] = new RasterizerState();
    rasterizerState[1]->CullMode(D3D11_CULL_NONE);    

    spriteBuffer = new SpriteBuffer;
    spriteBuffer->Get().maxFrame = { frameX, frameY };

    maxFrame.x = (int)frameX;
    maxFrame.y = (int)frameY;
}

Trail::~Trail()
{
    delete spriteBuffer;

    delete rasterizerState[0];
    delete rasterizerState[1];
}

void Trail::Update()
{
    if (!IsActive()) return;

    vector<VertexUV>& vertices = mesh->GetVertices();

    FOR(width + 1)
    {
        Vector3 startPos = vertices[i * 2].pos;
        Vector3 endPos = vertices[(i * 2) + 1].pos;

        Vector3 startDestPos;
        Vector3 endDestPos;

        if (i == 0)
        {
            startDestPos = start->GetGlobalPosition();
            endDestPos = end->GetGlobalPosition();

            startPos = startDestPos;
            endPos = endDestPos;
        }
        else
        {
            startDestPos = vertices[(i - 1) * 2].pos;
            endDestPos = vertices[(i - 1) * 2 + 1].pos;
        }

        startPos = GameMath::Lerp<Vector3>(startPos, startDestPos, speed * DELTA);
        endPos = GameMath::Lerp<Vector3>(endPos, endDestPos, speed * DELTA);

        vertices[i * 2].pos = startPos;
        vertices[i * 2 + 1].pos = endPos;
    }

    mesh->UpdateVertices();

    UpdateFrame();
}

void Trail::Render()
{
    if (!IsActive()) return;

    spriteBuffer->SetPS(10);    

    rasterizerState[1]->SetState();
    
    if (isAdditive)
        Environment::Get()->SetAdditive();
    else
        Environment::Get()->SetAlphaBlend(true);

    GameObject::Render();

    rasterizerState[0]->SetState();
    
    Environment::Get()->SetAlphaBlend(false);
}

void Trail::Init()
{
    vector<VertexUV>& vertices = mesh->GetVertices();

    FOR(width + 1)
    {
        vertices[i * 2].pos = start->GetGlobalPosition();        
        vertices[(i * 2) + 1].pos = end->GetGlobalPosition();        
    }

    mesh->UpdateVertices();
}

void Trail::CreateMesh()
{
    vector<VertexUV>& vertices = mesh->GetVertices();

    vertices.reserve((width + 1) * 2);

    FOR(width + 1)
    {
        VertexUV vertex;
        vertex.uv = {(float)i / (float)width, 0.0f};
        vertices.push_back(vertex);

        vertex.uv = {(float)i / (float)width, 1.0f};
        vertices.push_back(vertex);
    }

    vector<UINT>& indices = mesh->GetIndices();

    indices.reserve(width * 6);
    FOR(width)
    {
        indices.push_back(i * 2);
        indices.push_back(i * 2 + 2);
        indices.push_back(i * 2 + 1);

        indices.push_back(i * 2 + 1);
        indices.push_back(i * 2 + 2);
        indices.push_back(i * 2 + 3);
    }

    mesh->CreateMesh();
}

void Trail::UpdateFrame()
{
    time += DELTA;

    if (time >= FRAME_INTERVAL)
    {
        time -= FRAME_INTERVAL;

        curFrame = ++curFrame % (maxFrame.x * maxFrame.y);

        spriteBuffer->Get().curFrame.x = curFrame % maxFrame.x;
        spriteBuffer->Get().curFrame.y = curFrame / maxFrame.x;
    }
}
