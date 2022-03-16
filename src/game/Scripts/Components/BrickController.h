#pragma once
#include "../src/engine/ECS/ECS.h"
class BrickController : public Component
{
public:
	int health = 3;
public:
	void start() override;
	void OnCollisionEnter(Collider* collider) override;
	void Damage(int value);
	void SetColor();
	void Disable();
};