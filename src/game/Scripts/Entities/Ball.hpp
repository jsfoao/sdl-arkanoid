#pragma once
#include "../src/engine/Engine.h"
#include "../src/game/Scripts/Components/BallController.h"

class BallController;

class Ball : public Entity
{
public:
	float size = 64;

public:
	Ball()
	{
		addComponent<Renderer>();
		transform->scale = Vector2(10, 10);
		transform->position = Vector2(600, 600);

		BoxCollider* collider = addComponent<BoxCollider>();
		collider->layer = Layer_Ball;
		collider->collisionLayer = Layer_Brick + Layer_Wall + Layer_Player;
		collider->scale = transform->scale;

		addComponent<Rigidbody>();
		addComponent<BallController>();
	}
};