#include "PlayerController.h"
#include "../src/engine/Engine.h"
#include <iostream>

extern Engine* n_engine;
extern Input* n_input;

Rigidbody* rb;
void PlayerController::start()
{
	speed = 300.f;
	Instantiate(new Box(), Vector2(300, 300), Vector2(32, 32));
	Instantiate(new Box(), Vector2(500, 500), Vector2(32, 32));
	rb = owner->getComponent<Rigidbody>();
}

void PlayerController::update()
{
	if (Input::GetKey(SDL_SCANCODE_W))
	{
	}
}

void PlayerController::OnCollisionEnter(Collider* collider)
{
	if (collider->layer == Default)
	{
		std::cout << "Enter!" << std::endl;
		owner->getComponent<Renderer>()->color = Color::Black;
		collider->owner->getComponent<Renderer>()->color = Color::Green;
	}
}

void PlayerController::OnCollisionExit(Collider* collider)
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