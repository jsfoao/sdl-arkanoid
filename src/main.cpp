#include "engine/Engine.h"

extern Engine* n_engine;
extern Time* n_time;

int main()
{
	n_engine = new Engine();

	Uint64 previous_ticks = SDL_GetPerformanceCounter();

	n_engine->init("Nata Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, false);
	n_engine->start();
	while (n_engine->running())
	{
		Uint64 ticks = SDL_GetPerformanceCounter();
		Uint64 delta_ticks = ticks - previous_ticks;
		previous_ticks = ticks;
		n_time->deltaTime = (float)delta_ticks / SDL_GetPerformanceFrequency();

		n_engine->handleEvents();
		n_engine->update();
		n_engine->render();

		SDL_Delay(16);		
	}

	n_engine->clean();
}