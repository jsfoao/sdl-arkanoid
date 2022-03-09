#pragma once
#include "../../ECS/ECS.h"
#include "../../Color/Color.h"

class Renderer : public Component
{
public:
	Color color;

public:
	Renderer();
	~Renderer();
	void render() override;
};