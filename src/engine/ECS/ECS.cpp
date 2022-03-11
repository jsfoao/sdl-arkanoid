#include "ECS.h"
#include <iostream>
#include "../Engine.h"

Entity::Entity(){}

Entity::~Entity() {}

void Entity::destroy()
{
	active = false;
}

void Entity::start()
{
	for (int i = components.size() - 1; i >= 0; i--)
	{
		components[i]->start();
	}
}

void Entity::update()
{
	if (!active) { return; }

	for (int i = components.size() - 1; i >= 0; i--)
	{
		components[i]->update();
	}
}

void Entity::render()
{
	if (!active) { return; }

	for (int i = components.size() - 1; i >= 0; i--)
	{
		components[i]->render();
	}
}

Component::~Component() {}
void Component::start() {}
void Component::update() {}
void Component::render() {}
void Component::OnCollisionEnter(Collider* collider) {}
void Component::OnCollisionStay(Collider* collider) {}
void Component::OnCollisionExit(Collider* collider) {}