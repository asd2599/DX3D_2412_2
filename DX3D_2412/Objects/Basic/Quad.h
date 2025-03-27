#pragma once

class Quad : public GameObject<VertexUV>
{
public:
    Quad(Vector2 size);
    Quad(wstring texture);

    Vector2 GetSize() { return size; }

protected:
    Vector2 size;
};