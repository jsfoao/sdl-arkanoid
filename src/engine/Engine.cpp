#include "Engine.h"

Engine* n_engine = nullptr;
Input* n_input = nullptr;
Time* n_time = nullptr;
GameManager* n_game = nullptr;
int n_scancode = 0;

#pragma region Global funcs
Entity* Instantiate(Entity* entity)
{
	n_engine->addEntity(entity);

	for (int i = entity->components.size() - 1; i >= 0; i--)
	{
		entity->components[i]->start();
	}

	return entity;
};

Entity* Instantiate(Entity* entity, Vector2 position)
{
	entity->transform->position = position;
	n_engine->addEntity(entity);

	for (int i = entity->components.size() - 1; i >= 0; i--)
	{
		entity->components[i]->start();
	}

	return entity;
};

void Destroy(Entity* entity)
{
	for (size_t i = 0; i < entity->components.size(); i++)
	{
		delete entity->components[i];
	}
	n_engine->removeEntity(entity);
	delete entity;
}
#pragma endregion

#pragma region Engine
Engine::Engine() {}

Engine::~Engine() {}

void Engine::init(const char* title, int x, int y, int width, int height, bool fullscreen)
{
	// successfully initialized SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		printf("Engine init\n");
		window = new Window(title, x, y, width, height, fullscreen);
		renderer = SDL_CreateRenderer(window->sdl_window, -1, 0);
		n_input = new Input();
		n_time = new Time();
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
}

void Engine::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
			{
				isRunning = false;
				break;
			}
			case SDL_KEYDOWN:
			{
				n_scancode = event.key.keysym.scancode;
				n_input->keys[n_scancode] = true;
				break;
			}
			case SDL_KEYUP:
			{
				n_scancode = event.key.keysym.scancode;
				n_input->keys[n_scancode] = false;
				break;
			}
		}
	}
	Input::evaluateKeyState(n_scancode);
}

void Engine::start() 
{
	n_game->start();

	for (int i = entities.size() - 1; i >= 0; i--)
	{
		entities[i]->start();
	}
}

void Engine::update()
{
	for (int i = entities.size() - 1; i >= 0; i--)
	{
		entities[i]->update();
	}
}

void Engine::render()
{
	SDL_SetRenderDrawColor(renderer, 25, 25, 40, 255);
	SDL_RenderClear(renderer);

	for (int i = entities.size() - 1; i >= 0; i--)
	{
		entities[i]->render();
	}

	SDL_RenderPresent(renderer);
}

void Engine::clean()
{
	SDL_DestroyWindow(window->sdl_window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("Engine cleaned");
}
#pragma endregion

#pragma region Time
Time::Time() {}
Time::~Time() {}
float Time::deltaTime = 0.f;
#pragma endregion