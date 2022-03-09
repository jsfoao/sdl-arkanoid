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
#include "ECS/ECS.h"

enum Tag
{
	Default,
	Player,
	Ground
};

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
