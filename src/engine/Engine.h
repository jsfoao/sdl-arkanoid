#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <SDL/SDL.h>
#include "Vector/Vector2.h"
#include "Color/Color.h"
#include "Window/Window.h"
#include "Input/Input.h"

enum Tag
{
	Default,
	Player,
	Ground
};

#pragma region ECS
class Entity;
class Component;
class Transform;
class Renderer;

class Entity
{
public:
	bool active = true;
	std::vector<Component*> components;
	SDL_Renderer* sdl_renderer;
	Transform* transform;
	Renderer* renderer;

public:
	Entity();
	~Entity();
	void start();
	void update();
	void render();
	void destroy();

	template <typename T>
	T* addComponent();

	template <typename T>
	T* getComponent();

	void log();
};

class Component
{
public:
	bool active = true;
	Entity* owner;

	virtual ~Component();
	virtual void start();
	virtual void update();
	virtual void render();
};
#pragma endregion

#pragma region Components
class Transform : public Component
{
public:
	Vector2 position;
	Vector2 scale;

public:
	Transform();
	~Transform();
	void update() override;
};

class Renderer : public Component
{
public:
	Color color;

public:
	Renderer();
	~Renderer();
	void render() override;
};

class Collider : public Component
{
public:
	Vector2 position;
	Vector2 offset;
	Color color;
	Tag tag;
	bool isTrigger;
	Collider* other;

protected: 
	bool isColliding;

public:
	Collider();
	~Collider();
	void update() override;
	bool onCollision();
};

class BoxCollider : public Collider
{
public:
	Vector2 scale;

public:
	BoxCollider();
	void update() override;
	void render() override;
};
bool aabb_intersect(const BoxCollider* a, const BoxCollider* b);

class CircleCollider : public Collider
{
public:
	int radius;

public:
	CircleCollider();
	void update() override;
	void render() override;
};

bool circle_intersect(const CircleCollider* a, const CircleCollider* b);
bool aabb_circle_intersect(const BoxCollider* box, const CircleCollider* circle);
int clamp(int a, int min, int max);


class PlayerController : public Component
{
public:
	int speed;
public:
	PlayerController();
	void start() override;
	void update() override;
};
#pragma endregion

#pragma region Time
class Time
{
public:
	Time();
	~Time();

public:
	float deltaTime;
};
#pragma endregion

#pragma region Engine
class Engine
{
public:
	bool isRunning;
	Window* window;
	SDL_Renderer* renderer;
	Input* input;
	Time* time;
	std::vector<Entity*> entities;
	std::vector<Collider*> colliders;

public:
	Engine();
	~Engine();

	void init(const char* title, int x, int y, int width, int height, bool fullscreen);

	void handleEvents();
	void start();
	void update();
	void render();
	void clean();

	void addEntity(Entity* entity)
	{
		entity->sdl_renderer = renderer;
		entities.push_back(entity);
	}

	void removeEntity(Entity* entity)
	{
		for (size_t i = 0; i < entities.size(); i++)
		{
			if (entities[i] == entity)
			{
				entities.erase(std::next(entities.begin(), i));
			}
		}
	}

	bool running() { return isRunning; }
};
#pragma endregion
