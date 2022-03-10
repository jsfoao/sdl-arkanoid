#include "PlayerController.h"
#include "../src/engine/Engine.h"
#include <iostream>

extern Engine* n_engine;

void PlayerController::start()
{
	speed = 180;
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

void PlayerController::onCollisionEnter(Collider* collider)
{
	if (collider->layer == Default)
	{
		std::cout << "Enter!" << std::endl;
		owner->getComponent<Renderer>()->color = Color::Black;
		collider->owner->getComponent<Renderer>()->color = Color::Green;
	}
}

void PlayerController::onCollisionExit(Collider* collider)
{
	if (collider->layer == Default)
	{
		std::cout << "Exit!" << std::endl;
		owner->getComponent<Renderer>()->color = Color::White;
		collider->owner->getComponent<Renderer>()->color = Color::Red;
	}
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