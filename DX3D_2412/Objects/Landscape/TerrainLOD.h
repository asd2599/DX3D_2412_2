#pragma once

class TerrainLOD : public GameObject<VertexUV>
{
private:
    typedef VertexUV VertexType;

public:
    TerrainLOD(wstring heightFile);
    ~TerrainLOD();

    void Render();
    void GUIRender();

private:
    void MakeMesh();

private:
    FloatValueBuffer* terrainBuffer;
    FloatValueBuffer* heightBuffer;

    HullShader* hullShader;
    DomainShader* domainShader;

    Texture* heightMap;

    UINT cellsPerPatch = 32;
    float cellSpacing = 5;
    Vector2 cellUV;

    UINT width, height;
    UINT patchWidth, patchHeight;
};