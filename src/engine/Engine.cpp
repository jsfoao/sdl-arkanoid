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
Entity* box = nullptr;
Entity* box2 = nullptr;

void Engine::start() 
{
	// Player entity
	player = new Entity();
	player->transform->position = Vector2(100, 100);
	player->addComponent<PlayerController>();
	player->getComponent<BoxCollider>()->layer = Default;
	player->getComponent<BoxCollider>()->collisionLayer = Default;
	addEntity(player);

	// Box entity
	box = new Entity();
	box->transform->position = Vector2(400, 400);
	box->getComponent<BoxCollider>()->layer = Default;
	box->getComponent<BoxCollider>()->collisionLayer = Default;
	box->getComponent<Renderer>()->color = Color::Red;
	addEntity(box);

	// Box2 entity
	//box2 = new Entity();
	//box2->transform->position = Vector2(200, 400);
	//box2->getComponent<BoxCollider>()->layer = Default;
	//box2->getComponent<BoxCollider>()->collisionLayer = Default;
	//box2->getComponent<Renderer>()->color = Color::Red;
	//addEntity(box2);

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