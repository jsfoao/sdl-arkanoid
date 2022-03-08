#include "engine/engine.h"

Engine* n_engine = nullptr;
int main()
{
	n_engine = new Engine();

	const int fps = 144;
	const int frameDelay = 1000 / fps;

	Uint64 previous_ticks = SDL_GetPerformanceCounter();

	n_engine->init("Nata Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	n_engine->start();
	while (n_engine->running())
	{
		Uint64 ticks = SDL_GetPerformanceCounter();
		Uint64 delta_ticks = ticks - previous_ticks;
		previous_ticks = ticks;
		n_engine->time->deltaTime = (float)delta_ticks / SDL_GetPerformanceFrequency();

		n_engine->handleEvents();
		n_engine->update();
		n_engine->render();

		if (frameDelay > n_engine->time->deltaTime)
		{
			SDL_Delay(frameDelay - n_engine->time->deltaTime);
		}
		/*printf("FPS %f\n", 1.f / n_time->deltaTime);*/
	}

	n_engine->clean();
}