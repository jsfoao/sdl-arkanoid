#include "PlayerController.h"
#include "../src/engine/Engine.h"
#include <iostream>

extern Engine* n_engine;
extern Input* n_input;

int counter = 0;
void PlayerController::start()
{
	speed = 300.f;
}

void PlayerController::update()
{
	if (Input::GetKeyDown(SDL_SCANCODE_W))
	{
	}
	if (Input::GetKey(SDL_SCANCODE_W))
	{
	}
	if (Input::GetKeyUp(SDL_SCANCODE_W))
	{
	}

	std::cout << counter << std::endl;
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