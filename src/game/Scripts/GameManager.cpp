#include "GameManager.h"
#include "SDL/SDL.h"

extern Engine* n_engine;
void GenerateMap();

Entity* player = nullptr;
Entity* ball = nullptr;

void GameManager::start()
{
	player = Instantiate(new Player(), Vector2(400, 560));
	ball = Instantiate(new Ball(), Vector2(400, 500));

	GenerateMap();
}

static void GenerateMap()
{
	for (size_t y = 0; y < 16; y++)
	{
		for (size_t x = 0; x < 16; x++)
		{
			Instantiate(new Brick(), Vector2((x + 0.5) * 50, (y + 0.5) * 25));
		}
	}
}