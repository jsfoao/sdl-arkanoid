#include "nata.h"

#pragma region Engine
Engine::Engine() {}
Engine::~Engine() {}

void Engine::init(const char* title, int x, int y, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// successfully initialized SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		printf("Engine init");
		window = SDL_CreateWindow(title, x, y, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
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
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	}
}

void Engine::update()
{

}

void Engine::render()
{
	SDL_SetRenderDrawColor(renderer, 25, 25, 40, 255);
	SDL_RenderClear(renderer);
	// stuff to render
	// ...
	SDL_RenderPresent(renderer);
}

void Engine::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("Engine cleaned");
}
#pragma endregion

#pragma region Time
Time::Time() {}
Time::~Time() {}
#pragma endregion
