#include <stdio.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include "engine/nata.h"

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Event event;

	bool running = true;
	Uint64 start_ticks = SDL_GetPerformanceCounter();
	Uint64 previous_ticks = SDL_GetPerformanceCounter();
	while (running)
	{
		Uint64 ticks = SDL_GetPerformanceCounter();
		Uint64 delta_ticks = ticks - previous_ticks;
		previous_ticks = ticks;
		float delta_time = (float)delta_ticks / SDL_GetPerformanceFrequency();

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					running = false;
			}
		}

		SDL_SetRenderDrawColor(renderer, 25, 25, 40, 255);;
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}
}