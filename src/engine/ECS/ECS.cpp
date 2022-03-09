#include "ECS.h"
#include <iostream>
#include "../Engine.h"

Entity::Entity()
{
	transform = addComponent<Transform>();
	renderer = addComponent<Renderer>();
}

Entity::~Entity() {}

void Entity::destroy()
{
	active = false;
}

void Entity::start()
{
	for (Component* c : components)
	{
		c->start();
	}
}

void Entity::update()
{
	if (!active) { return; }

	for (Component* c : components)
	{
		c->update();
	}
}

void Entity::render()
{
	if (!active) { return; }

	for (Component* c : components)
	{
		c->render();
	}
}

void Entity::log()
{
	std::cout << "Position: ";
	transform->position.print();
}

Component::~Component() {}
void Component::start() {}
void Component::update() {}
void Component::render() {}