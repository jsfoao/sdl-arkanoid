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
		input = new Input();
		isRunning = true;
		start();
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

void Engine::start(){}

void Engine::update()
{
	if (input->GetKeyDown(SDL_SCANCODE_W))
	{
		printf("W down\n");
	}
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

#pragma region Input
Input::Input() {}
Input::~Input() {}

bool Input::GetKeyDown(int scancode)
{
	return keys[scancode] == true;
}

bool Input::GetKeyUp(int scancode)
{
	return keys[scancode] == false;
}

void Input::SetKeyState(int scancode, bool state)
{
	keys[scancode] = state;
}
#pragma endregion

#pragma region Time
Time::Time() {}
Time::~Time() {}
#pragma endregion