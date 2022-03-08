#pragma once
#include "Vector2.h"
#include "Color.h"
#include <SDL/SDL.h>

class GameObject
{
public:
	bool active;
	Vector2 position;
	Vector2 scale;

	Color color;

public:
	GameObject();
	~GameObject();
	
	GameObject(const Vector2& position, const Vector2& scale, const Color& color);

	void update();
	void render(SDL_Renderer* renderer);
};