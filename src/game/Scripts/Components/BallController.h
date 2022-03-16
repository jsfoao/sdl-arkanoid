#pragma once
#include "../src/engine/ECS/ECS.h"
#include "../src/engine/Components/Core/Rigidbody.h"

class BallController : public Component
{
public:
	float speed;
	int damage;
	float angleFactor;

public:
	void start() override;
	void update() override;
	void OnCollisionEnter(Collider* collider) override;

	void WindowCollision();
};