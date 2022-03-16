#include "GameManager.h"
#include "SDL/SDL.h"

extern Engine* n_engine;

GameManager* gameManager = nullptr;

void GenerateMap();

Entity* player = nullptr;
Entity* ball = nullptr;

void GameManager::start()
{
	gameManager = this;
	GenerateMap();

	player = Instantiate(new Player(), Vector2(n_engine->window->width / 2, n_engine->window->height - 50.f));
	ball = Instantiate(new Ball(), Vector2(400, 500));
	ball->getComponent<BallController>()->holding = true;
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