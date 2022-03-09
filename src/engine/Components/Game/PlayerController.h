#pragma once
#include "../../ECS/ECS.h"

class PlayerController : public Component
{
public:
	int speed;
public:
	void start() override;
	void update() override;
	void onCollisionEnter(Collider* collider) override;
	void onCollisionExit(Collider* collider) override;
};