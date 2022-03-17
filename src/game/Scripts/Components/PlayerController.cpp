#include "PlayerController.h"
#include "../src/engine/Engine.h"

extern Engine* n_engine;
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
		if (!(owner->transform->position.x + speed * Time::deltaTime > n_engine->window->width - width / 2))
		{
			owner->transform->position.x += speed * Time::deltaTime;
		}
	}

	if (Input::GetKey(SDL_SCANCODE_A))
	{
		if (!(owner->transform->position.x - speed * Time::deltaTime < 0.f + width / 2))
		{
			owner->transform->position.x -= speed * Time::deltaTime;
		}
	}
}