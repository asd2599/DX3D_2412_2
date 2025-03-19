#include "Framework.h"
#include "WeatherScene.h"

WeatherScene::WeatherScene()
{
	collider = new BoxCollider(Vector3(50, 50, 1));	
	//particle = new Sprite(L"Resources/Textures/FX/Lightning_8x1.png", 50, 10, 1, 8);
    //particle = new Spark(L"Resources/Textures/FX/star.png", true);
    //particle = new Rain();
    //particle = new Snow();
    particle = new ParticleSystem("Resources/FX/Explosion.fx");
}

WeatherScene::~WeatherScene()
{
	delete collider;
	delete particle;
}

void WeatherScene::Update()
{
    if (KEY->Down(VK_LBUTTON))
    {
        Ray ray = CAM->ScreenPointToRay(mousePos);
        RaycastHit hit;

        if (collider->IsRayCollision(ray, &hit))
        {
            particle->Play(hit.point);
        }
    }

    particle->Update();
}

void WeatherScene::PreRender()
{
}

void WeatherScene::Render()
{
	collider->Render();
    particle->Render();
}

void WeatherScene::PostRender()
{
}

void WeatherScene::GUIRender()
{
    //particle->GUIRender();
}
