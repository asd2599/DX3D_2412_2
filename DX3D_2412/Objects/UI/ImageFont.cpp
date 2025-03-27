#include "Framework.h"

ImageFont::ImageFont(wstring texturePath, float interval)
{
    LoadTextures(texturePath);

    fontSize = textures[0]->GetSize();

    quads.resize(LENGTH);

    FOR(LENGTH)
    {
        quads[i] = new Quad(fontSize);
        quads[i]->SetParent(this);
    }
}

ImageFont::~ImageFont()
{
    for (Quad* quad : quads)
        delete quad;
}

void ImageFont::Render()
{
    FOR(strValue.size())
    {
        int num = strValue[i] - '0';
        int index = strValue.size() - i - 1;

        quads[index]->GetMaterial()->SetDiffuseMap(textures[num]);
        quads[index]->Render();
    }
}

void ImageFont::SetValue(UINT value)
{
    strValue = to_string(value);

    float start = 0.0f;
    float intervalSize = interval * (strValue.size() - 1);

    switch (alignedType)
    {
    case L:
        start = fontSize.x * strValue.size() + intervalSize;
        break;
    case C:
        start = (fontSize.x * strValue.size() + intervalSize) * 0.25f;
        break;    
    }

    FOR(strValue.size())
    {
        float x = i * -quads[i]->GetSize().x - interval * i + start;

        quads[i]->SetLocalPosition(x, 0, 0);
        quads[i]->UpdateWorld();
    }
}

void ImageFont::LoadTextures(wstring path)
{
    WIN32_FIND_DATA findData;

    wstring file = path + L"*.png";
    HANDLE handle = FindFirstFile(file.c_str(), &findData);

    bool result = true;    

    while (result)
    {
        Texture* texture = Texture::Add(path + findData.cFileName);

        textures.push_back(texture);

        result = FindNextFile(handle, &findData);
    }
}
