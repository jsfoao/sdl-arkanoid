#pragma once
#include "../src/engine/Engine.h"
#include "../src/game/Scripts/Components/PlayerController.h"

class PlayerController;

class Player : public Entity
{
public:
	Player()
	{
		addComponent<Renderer>();

		BoxCollider* collider = addComponent<BoxCollider>();
		collider->layer = Layer_Player;
		collider->collisionLayer = Layer_Ball;
		collider->scale = transform->scale;

		addComponent<PlayerController>();
	}
};