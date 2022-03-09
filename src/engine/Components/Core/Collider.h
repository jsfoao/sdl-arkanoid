#pragma once
#include <iostream>
#include "../../ECS/ECS.h"
#include "../../Vector/Vector2.h"
#include "../../Color/Color.h"
#include <bitset>

enum CollisionLayer
{
	Default = 0b00000001,
	Player = 0b00000010,
	Ground = 0b00000100
};

class Collider : public Component
{
public:
	Vector2 position;
	Vector2 offset;
	Collider* other;
	std::bitset<8> layer;
	std::bitset<8> collisionLayer;

	// Gizmos
	Color color;

protected:
	bool isColliding;

public:
	Collider();
	~Collider();
	void update() override;
	bool onCollision();
};

class BoxCollider : public Collider
{
public:
	Vector2 scale;

public:
	BoxCollider();
	void update() override;
	void render() override;
};
bool aabb_intersect(const BoxCollider* a, const BoxCollider* b);

class CircleCollider : public Collider
{
public:
	int radius;

public:
	CircleCollider();
	void update() override;
	void render() override;
};

bool circle_intersect(const CircleCollider* a, const CircleCollider* b);
bool aabb_circle_intersect(const BoxCollider* box, const CircleCollider* circle);
int clamp(int a, int min, int max);