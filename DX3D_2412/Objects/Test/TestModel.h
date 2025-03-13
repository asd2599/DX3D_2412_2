#pragma once

class TestModel
{
public:
    TestModel();
    ~TestModel();

    void Update();
    void Render();
    void Edit();

    void SetPixelShader(wstring shaderFile);

private:
    Sphere* sphere;
    Model* model;
    ModelAnimator* animator;
};