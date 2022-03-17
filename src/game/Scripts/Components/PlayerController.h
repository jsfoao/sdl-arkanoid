#pragma once
#include "../src/engine/ECS/ECS.h"

class PlayerController : public Component
{
public:
	float speed;
	float width;

public:
	void start() override;
	void update() override;
};