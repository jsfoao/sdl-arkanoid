#pragma once
#include "../../ECS/ECS.h"

class Empty : public Entity {};

class Box : public Entity
{
public:
	Box()
	{
		addComponent<Renderer>();

		BoxCollider* collider = addComponent<BoxCollider>();
		collider->layer = Layer_All;
		collider->collisionLayer = Layer_All;
		collider->scale = transform->scale;
	}
};