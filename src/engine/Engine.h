#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <SDL/SDL.h>
#include "Vector2.h"
#include "Color.h"
#include "Window.h"


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
	std::string tag;
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

bool aabb_circle_intersect(const CircleCollider* a, const CircleCollider* b);
int clamp(int a, int min, int max);


class PlayerController : public Component
{
public:
	int speed;
public:
	PlayerController();
	void update() override;
};
#pragma endregion

#pragma region Input
class Input
{
public:
	bool keys[SDL_NUM_SCANCODES];
public:
	Input();
	~Input();

	bool GetKeyDown(int scancode);
	bool GetKeyUp(int scancode);
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

	bool running() { return isRunning; }
};
#pragma endregion
