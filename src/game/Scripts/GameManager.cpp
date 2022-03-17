#include "GameManager.h"
#include "SDL/SDL.h"


extern Engine* n_engine;

Entity* player = nullptr;
Entity* ball = nullptr;

void GameManager::start()
{
	std::string level = LoadFile(".\\src\\game\\Levels\\Level01.txt");
	GenerateMap(level);

	player = Instantiate(new Player(), Vector2(n_engine->window->width / 2, n_engine->window->height - 50.f));
	ball = Instantiate(new Ball(), Vector2(400, 500));
	ball->getComponent<BallController>()->holding = true;
}