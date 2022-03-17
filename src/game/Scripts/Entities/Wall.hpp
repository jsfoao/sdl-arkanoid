#pragma once
#include "../src/engine/Engine.h"

class Wall : public Entity
{
public:
	Wall()
	{
		transform->scale = Vector2(50, 25);
		Renderer* renderer;
		BoxCollider* collider;

		renderer = addComponent<Renderer>();
		renderer->color = Color::Black;
		renderer->outlineColor = Color::White;
		renderer->outline = true;

		collider = addComponent<BoxCollider>();
		collider->layer = Layer_Wall;
		collider->collisionLayer = Layer_Ball;
		collider->scale = transform->scale;
	}
};