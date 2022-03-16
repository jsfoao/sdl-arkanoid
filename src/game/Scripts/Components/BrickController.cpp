#include "BrickController.h"
#include "../src/engine/Engine.h"
#include <iostream>

void BrickController::start()
{
	health = 3;
	SetColor();
}

void BrickController::OnCollisionEnter(Collider* collider)
{
	if (collider->layer == Layer_Ball)
	{
		Damage(collider->owner->getComponent<BallController>()->damage);
	}
}

void BrickController::Damage(int value)
{
	health -= value;
	SetColor();
	if (health <= 0)
	{
		Destroy(owner);
	}
}

void BrickController::SetColor()
{
	Renderer* renderer = owner->getComponent<Renderer>();

	if (health == 1)
	{
		renderer->color = Color::Red;
	}
	else if (health == 2)
	{
		renderer->color = Color::Blue;
	}
	else if (health == 3)
	{
		renderer->color = Color::Green;
	}
}

void BrickController::Disable()
{
	owner->getComponent<Renderer>()->active = false;
}