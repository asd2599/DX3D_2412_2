#pragma once

class Player : public SphereCollider
{
private:
	const float GRAVITY = 9.8f;
	const float JUMP_POWER = 10.0f;

public:
	Player();
	~Player();

	void Update();
	void Render();
	void PostRender();	
	
private:
	void Control();
	void Fire();
	void Jump();
	void Move();
	//void Rotate();

	void CreateBullets();

	void SetCursor();

private:
	float moveSpeed = 5.0f;
	float rotSpeed = 1.0f;

	Vector3 velocity;

	POINT clientCenterPos;

	LightBuffer::Light* light;
};