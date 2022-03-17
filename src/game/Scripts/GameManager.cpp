#include "GameManager.h"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"


extern Engine* n_engine;

Entity* player = nullptr;

std::vector<std::string> levels;

int ballCount;
int health;
int score;

void GameManager::start()
{
	health = 3;
	levels.push_back(LoadFile(".\\src\\game\\Levels\\Level01.txt"));
	levels.push_back(LoadFile(".\\src\\game\\Levels\\Level02.txt"));
	levels.push_back(LoadFile(".\\src\\game\\Levels\\Level03.txt"));
	
	n_engine->resetScene();
	LoadLevel(levels[2]);

	std::cout << "Health: " << health << std::endl;
}

void GameManager::LoadLevel(std::string level)
{
	GenerateMap(level);

	if (player == nullptr)
	{
		player = Instantiate(new Player(), Vector2(n_engine->window->width / 2, n_engine->window->height - 50.f));
	}
	SpawnBall();
}

void GameManager::DamagePlayer()
{
	health--;
	std::cout << "Health: " << health << std::endl;
	if (health <= 0)
	{
		DeathBehaviour();
		return;
	}

	if (ballCount == 0)
	{
		SpawnBall();
	}
}

Ball* GameManager::SpawnBall()
{
	std::cout << "spawn ball" << std::endl;
	Entity* ball = Instantiate(new Ball(), Vector2(player->transform->position.x, player->transform->position.y - 20.f));
	ball->getComponent<BallController>()->holding = true;
	ballCount++;
	return ((Ball*)ball);
}

void GameManager::DestroyBall()
{
	ballCount--;
}

void GameManager::DeathBehaviour()
{
	std::cout << "ded" << std::endl;
}

void GameManager::IncrementScore(int value)
{
	score += value;
}

void GameManager::ResetScore()
{
	score = 0;
}