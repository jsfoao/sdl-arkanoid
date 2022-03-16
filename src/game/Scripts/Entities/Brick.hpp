#pragma once
#include "../src/engine/Engine.h"
#include "../src/game/Scripts/Components/BrickController.h"

class BrickController;

class Brick : public Entity
{
public:
	Brick()
	{
		transform->scale = Vector2(50, 25);
		Renderer* renderer;
		BoxCollider* collider;

		renderer = addComponent<Renderer>();
		renderer->outlineColor = Color::White;
		renderer->outline = true;

		collider = addComponent<BoxCollider>();
		collider->layer = Layer_Brick;
		collider->collisionLayer = Layer_Ball;
		collider->scale = transform->scale;

		addComponent<BrickController>();
	}
};