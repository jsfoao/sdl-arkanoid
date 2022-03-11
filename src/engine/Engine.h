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
#include "Components/Core/Transform.h"
#include "Components/Core/Renderer.h"
#include "Components/Core/Collider.h"
#include "Entities/Core/CoreEntities.h"

#include "../game/Game.h"

#pragma region Time
class Time
{
public:
	Time();
	~Time();

public:
	static float deltaTime;
};
#pragma endregion

class Engine
{
public:
	bool isRunning;
	Window* window;
	SDL_Renderer* renderer;
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

	Entity* Instantiate(Entity* entity)
	{
		addEntity(entity);
		return entity;
	};

	Entity* Instantiate(Entity* entity, Vector2 position)
	{
		entity->transform->position = position;
		addEntity(entity);
		return entity;
	};

	Entity* Instantiate(Entity* entity, Vector2 position, Vector2 scale)
	{
		entity->transform->position = position;
		entity->transform->scale = scale;
		addEntity(entity);
		return entity;
	};

	void Destroy(Entity* entity)
	{
		removeEntity(entity);
		delete entity;
	}

	bool running() { return isRunning; }
};