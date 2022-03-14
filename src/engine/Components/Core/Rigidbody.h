#pragma once
#include "../src/engine/Engine.h"
#include "../src/engine/ECS/ECS.h"
#include "Transform.h"
#include "../../Vector/Vector2.h"

class Rigidbody : public Component
{
public:
	Vector2 velocity;

public:
	void update();
};