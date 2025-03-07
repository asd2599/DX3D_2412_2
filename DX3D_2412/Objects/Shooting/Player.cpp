#include "Framework.h"

Player::Player()
{
	tag = "Player";

	localPosition.y = radius;	

	//clientCenterPos = { SCREEN_WIDTH >> 1, SCREEN_HEIGHT >> 1 };
	//ClientToScreen(hWnd, &clientCenterPos);
	//SetCursorPos(clientCenterPos.x, clientCenterPos.y);	
	//ShowCursor(false);	

	CreateBullets();

	//CAM->SetLocalPosition(0, 0, 0);
	//CAM->SetLocalRotation(0, 0, 0);
	//CAM->SetParent(this);

	light = Environment::Get()->GetLight(0);
	light->type = 2;
	light->color = { 1, 1, 1, 1 };
	light->range = 50.0f;
	light->attentionIntensity = 0.2f;
	light->inner = 30.0f;
	light->outer = 35.0f;

	CAM->SetTarget(this);
	CAM->TargetOptionLoad("ShootingView");
}

Player::~Player()
{		
	BulletManager::Delete();
}

void Player::Update()
{	
	if (UIManager::Get()->IsPopup())
		return;

	light->position = localPosition;
	light->direction = GetForward();

	//SetCursor();
	Control();
	Fire();
	Jump();
	Move();
	Rotate();

	UpdateWorld();	

	BulletManager::Get()->Update();
}

void Player::Render()
{
	Collider::Render();

	BulletManager::Get()->Render();
}

void Player::PostRender()
{
}

void Player::Control()
{
	Vector3 dir;

	if (KEY->Press('W'))
		dir += Vector3::Forward();
	if (KEY->Press('S'))
		dir += Vector3::Back();
	if (KEY->Press('A'))
		dir += Vector3::Left();
	if (KEY->Press('D'))
		dir += Vector3::Right();

	dir.Normalize();

	velocity.x = dir.x;
	velocity.z = dir.z;	

	//Vector3 delta = mousePos - CENTER;
	//Rotate(Vector3::Up(), delta.x * rotSpeed * DELTA);
	//CAM->Rotate(Vector3::Left(), delta.y * rotSpeed * DELTA);

	if (KEY->Down(VK_SPACE))
	{
		velocity.y = JUMP_POWER;
	}
}

void Player::Fire()
{
	if (KEY->Down(VK_LBUTTON))
	{
		//Bullet* bullet = bullets->Pop();
		//bullet->Fire(localPosition, GetForward());

		//UIManager::Get()->Mining();

		BulletManager::Get()->Fire(localPosition, GetForward());
	}

	if (KEY->Down(VK_RBUTTON))
	{
		//UIManager::Get()->Build();
	}
}

void Player::Jump()
{
	velocity.y -= GRAVITY * DELTA;

	float bottomHeight = BlockManager::Get()->GetHeight(localPosition);

	if (velocity.y < 0 && localPosition.y - radius <= bottomHeight)
	{
		velocity.y = 0.0f;
	}
}

void Player::Move()
{
	if (UIManager::Get()->IsPopup())
		return;

	Translate(velocity * moveSpeed * DELTA);
}

void Player::Rotate()
{
	Vector3 screenPos = CAM->WorldToScreenPoint(localPosition);

	Vector3 direction = (mousePos - screenPos).GetNormalized();

	float angle = atan2(direction.x, direction.y);

	localRotation.y = angle;
}

void Player::CreateBullets()
{
	//bullets = new PoolingManager<Bullet>();
	//bullets->Create(10);

	BulletManager::Get();
}

void Player::SetCursor()
{
	//if(UIManager::Get()->)

	SetCursorPos(clientCenterPos.x, clientCenterPos.y);
}
