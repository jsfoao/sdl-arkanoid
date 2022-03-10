#pragma once
#include "../../ECS/ECS.h"

class Empty : public Entity 
{
public:
	Empty()
	{
		transform = addComponent<Transform>();
	}
};

class Box : public Entity
{
public:
	Box()
	{
		transform = addComponent<Transform>();
		addComponent<Renderer>();

		BoxCollider* collider = addComponent<BoxCollider>();
		collider->layer = All;
		collider->collisionLayer = All;
		collider->scale = transform->scale;
	}
};