#include "ECS.h"
#include <iostream>
#include "../Engine.h"

Entity::Entity()
{
	transform = addComponent<Transform>();
}

Entity::~Entity() {}

void Entity::destroy()
{
	active = false;
}

void Entity::start()
{
	for (int i = components.size() - 1; i >= 0; i--)
	{
		if (components.size() == 0)
		{
			return;
		}
		components[i]->start();
	}
}

void Entity::update()
{
	if (!active) { return; }

	for (int i = components.size() - 1; i >= 0; i--)
	{
		if (components.size() == 0)
		{
			return;
		}
		components[i]->update();
	}
}

void Entity::render()
{
	if (!active) { return; }

	for (int i = components.size() - 1; i >= 0; i--)
	{
		if (components.size() == 0)
		{
			return;
		}
		components[i]->render();
	}
}

Component::~Component() {}
void Component::start() {}
void Component::update() 
{
	if (!active)
	{
		return;
	}
}
void Component::render() 
{
	if (!active)
	{
		return;
	}
}
void Component::OnCollisionEnter(Collider* collider) {}
void Component::OnCollisionStay(Collider* collider) {}
void Component::OnCollisionExit(Collider* collider) {}