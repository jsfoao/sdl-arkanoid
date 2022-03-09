#pragma once
#include "../../ECS/ECS.h"
#include "../../Vector/Vector2.h"

class Transform : public Component
{
public:
	Vector2 position;
	Vector2 scale;

public:
	Transform();
	~Transform();
	void update() override;
};