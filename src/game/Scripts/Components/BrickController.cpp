#include "BrickController.h"
#include "../src/engine/Engine.h"
#include <iostream>

extern int ballCount;
void BrickController::start()
{
	health = 3;
	ballChance = 5;
	SetColor();
}

void BrickController::Damage(int value)
{
	health -= value;
	SetColor();
	if (health <= 0)
	{
		float random = rand() % 100;
		std::cout << random << std::endl;
		if (random <= ballChance)
		{
			Instantiate(new Ball(), owner->transform->position);
			ballCount++;
		}
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