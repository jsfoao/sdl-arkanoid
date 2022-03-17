#pragma once
#include "../src/engine/Engine.h"
#include "Entities/Brick.hpp"
#include "Entities/Player.hpp"
#include "Entities/Ball.hpp"
#include "Entities/Wall.hpp"
#include "../src/game/Scripts/Components/PlayerController.h"
#include "LevelManager.h"

class GameManager : Entity
{
public:
	void start();

	void LoadLevel(std::string level);
	void DamagePlayer();
	void DeathBehaviour();
	Ball* SpawnBall();
	void DestroyBall();
	void IncrementScore(int value);
	void ResetScore();
};