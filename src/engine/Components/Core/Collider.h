#pragma once
#include <iostream>
#include "../../ECS/ECS.h"
#include "../../Vector/Vector2.h"
#include "../../Color/Color.h"
#include <bitset>

enum CollisionLayer
{
	Layer_Default = 0b00000001,
	Layer_Player = 0b00000010,
	Layer_Ground = 0b00000100,
	Layer_Brick = 0b00001000,
	Layer_Ball = 0b00010000,
	Layer_Wall = 0b00100000,
	Layer_All = 0b11111111
};

class Collider : public Component
{
public:
	Vector2 position;
	Vector2 offset;
	Collider* other;
	std::bitset<8> layer;
	std::bitset<8> collisionLayer;
	Collider* lastCollider;

	// Gizmos
	Color color = Color::Green;
	bool drawGizmos = false;

public:
	Collider();
	~Collider();
	void update() override;
	void notifyComponentsEnter(Collider* collider);
	void notifyComponentsStay(Collider* collider);
	void notifyComponentsExit(Collider* collider);
	bool isColliding(Collider* collider);
};

class BoxCollider : public Collider
{
public:
	Vector2 scale;
	Vector2 collisionFace;

public:
	BoxCollider();
	void update() override;
	void render() override;
	bool isColliding(Collider* collider);
	void evaluateCollision(Collider* collider);
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