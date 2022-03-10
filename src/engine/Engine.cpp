#include "Engine.h"

Engine* n_engine = nullptr;

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
		input = new Input();
		time = new Time();
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
				int scancode = event.key.keysym.scancode;
				input->keys[scancode] = true;
				break;
			}
			case SDL_KEYUP:
			{
				int scancode = event.key.keysym.scancode;
				input->keys[scancode] = false;
				break;
			}
		}
	}
}

// Entities
Entity* player = nullptr;
Entity* empty = nullptr;

void Engine::start() 
{
	// Player entity
	player = Instantiate(new Box(), Vector2(100, 100), Vector2(32, 32));
	player->addComponent<PlayerController>();

	empty = Instantiate(new Empty());

	for (Entity* entity : entities)
	{
		entity->start();
	}
}

void Engine::update()
{
	for (Entity* entity : entities)
	{
		entity->update();
	}
}

void Engine::render()
{
	SDL_SetRenderDrawColor(renderer, 25, 25, 40, 255);
	SDL_RenderClear(renderer);

	for (Entity* entity : entities)
	{
		entity->render();
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
#pragma endregion