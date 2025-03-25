#pragma once

class ModelAnimatorInstancing : public ModelAnimator
{
private:
    class FrameInstancingBuffer : public ConstBuffer
    {
    public:
        struct Data
        {
            Motion motions[MAX_INSTANCE];
        };

    public:
        FrameInstancingBuffer() : ConstBuffer(&data, sizeof(Data))
        {
        };

        Data* GetData() { return &data; }

    private:
        Data data;
    };

public:
    ModelAnimatorInstancing(string name);
    ~ModelAnimatorInstancing();

    void Update();
    void Render();
    void Edit();

    Transform* Add();

    void PlayClip(UINT instanceIndex, int clip, float scale = 1.0f, float takeTime = 0.1f);

    Motion* GetMotion(UINT instanceIndex)
    {
        return &frameInstancingBuffer->GetData()->motions[instanceIndex];
    }

    UINT GetClipSize() { return clips.size(); }

private:
    vector<Transform*> transforms;
    InstanceData instanceDatas[MAX_INSTANCE];

    VertexBuffer* instanceBuffer;
    FrameInstancingBuffer* frameInstancingBuffer;

    UINT drawCount = 0;
};