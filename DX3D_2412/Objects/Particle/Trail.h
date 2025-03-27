#pragma once

class Trail : public GameObject<VertexUV>
{
private:
    const float FRAME_INTERVAL = 0.05f;

public:
    Trail(wstring imageFile, Transform* start, Transform* end,
        UINT width, float frameX = 1, float frameY = 1, bool isAdditive = true);
    ~Trail();

    void Update();
    void Render();

    void Init();

    void SetSpeed(float speed) { this->speed = speed; }    

private:
    void CreateMesh();
    void UpdateFrame();

private:
    Transform* start, *end;

    UINT width;
    UINT curFrame = 0;
    float speed = 1.0f;
    float time = 0.0f;    
    POINT maxFrame;
    bool isAdditive;

    RasterizerState* rasterizerState[2];

    SpriteBuffer* spriteBuffer;
};