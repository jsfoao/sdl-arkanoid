#include "PlayerController.h"
#include "../src/engine/Engine.h"
#include <iostream>

static Rigidbody* rb;
static float speed;

void PlayerController::start()
{
	speed = 200.f;
	width = 64.f;
	owner->transform->scale = Vector2(width, 16.f);
}

void PlayerController::update()
{
	if (Input::GetKey(SDL_SCANCODE_D))
	{
		owner->transform->position.x += speed * Time::deltaTime;
	}

	if (Input::GetKey(SDL_SCANCODE_A))
	{
		owner->transform->position.x -= speed * Time::deltaTime;
	}

	//if (Input::GetKey(SDL_SCANCODE_W))
	//{
	//	owner->transform->position.y -= speed * Time::deltaTime;
	//}

	//if (Input::GetKey(SDL_SCANCODE_S))
	//{
	//	owner->transform->position.y += speed * Time::deltaTime;
	//}
}

void PlayerController::OnCollisionEnter(Collider* collider)
{
}











// friction notes
// move
//if (move_right())
//{
//	velX += speed * deltaTime;
//}
//
//// apply friction
//velX -= velX * friction_coefficient * deltaTime;
//
//// apply velocity to position
//posX += velX * deltaTime;