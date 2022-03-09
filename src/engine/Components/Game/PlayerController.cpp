#include "PlayerController.h"
#include "../../Engine.h"

extern Engine* n_engine;

void PlayerController::start()
{
	speed = 200;
}

void PlayerController::update()
{
	if (n_engine->input->GetKeyDown(SDL_SCANCODE_W))
	{
		owner->transform->position.y -= speed * n_engine->time->deltaTime;
	}
	if (n_engine->input->GetKeyDown(SDL_SCANCODE_S))
	{
		owner->transform->position.y += speed * n_engine->time->deltaTime;
	}
	if (n_engine->input->GetKeyDown(SDL_SCANCODE_A))
	{
		owner->transform->position.x -= speed * n_engine->time->deltaTime;
	}
	if (n_engine->input->GetKeyDown(SDL_SCANCODE_D))
	{
		owner->transform->position.x += speed * n_engine->time->deltaTime;
	}
}