#pragma once
#include "../../ECS/ECS.h"
#include "../../Color/Color.h"

class Renderer : public Component
{
public:
	Color color;
	Color outlineColor;
	bool outline;

public:
	Renderer();
	~Renderer();
	void render() override;
};