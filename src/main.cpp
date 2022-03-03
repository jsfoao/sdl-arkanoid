#include "engine/nata.h"

Engine* n_engine = nullptr;
Time* n_time = nullptr;
int main()
{
	n_engine = new Engine();
	n_time = new Time();

	const int fps = 144;
	const int frameDelay = 1000 / fps;

	Uint64 previous_ticks = SDL_GetPerformanceCounter();

	n_engine->init("Nata Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	while (n_engine->running())
	{
		Uint64 ticks = SDL_GetPerformanceCounter();
		Uint64 delta_ticks = ticks - previous_ticks;
		previous_ticks = ticks;
		n_time->deltaTime = (float)delta_ticks / SDL_GetPerformanceFrequency();

		n_engine->handleEvents();
		n_engine->update();
		n_engine->render();

		if (frameDelay > n_time->deltaTime)
		{
			SDL_Delay(frameDelay - n_time->deltaTime);
		}
		/*printf("FPS %f\n", 1.f / n_time->deltaTime);*/
	}

	n_engine->clean();
}