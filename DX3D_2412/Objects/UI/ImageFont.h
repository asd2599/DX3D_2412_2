#pragma once

class ImageFont : public Transform
{
public:
    enum AlignedType
    {
        L, C, R
    };

private:
    const UINT LENGTH = 8;

public:
    ImageFont(wstring texturePath, float interval = 1.0f);
    ~ImageFont();

    void Render();

    void SetValue(UINT value);
    void SetAligned(AlignedType type) { alignedType = type; }

private:
    void LoadTextures(wstring path);

private:
    UINT value = 0;
    string strValue;

    vector<Quad*> quads;
    vector<Texture*> textures;
    FloatValueBuffer* valueBuffer;

    float interval;

    AlignedType alignedType;
    Vector2 fontSize;
};