#pragma once
#include "../src/engine/ECS/ECS.h"
class BrickController : public Component
{
public:
	int health = 3;
	int ballChance;

public:
	void start() override;
	void Damage(int value);
	void SetColor();
	void Disable();
};