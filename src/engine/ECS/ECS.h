#pragma once
#include <vector>
#include "SDL/SDL.h"
#include "../Vector/Vector2.h"
#include "../Color/Color.h"

#pragma region ECS
class Entity;
class Component;
class Transform;
class Renderer;

class Entity
{
public:
	bool active = true;
	std::vector<Component*> components;
	SDL_Renderer* sdl_renderer;
	Transform* transform;
	Renderer* renderer;

public:
	Entity();
	~Entity();
	void start();
	void update();
	void render();
	void destroy();

	void AddCollider();

	template <typename T>
	T* addComponent()
	{
		T* newComponent = new T();
		newComponent->owner = this;
		components.push_back(newComponent);
		return newComponent;
	}

	template <typename T>
	T* getComponent()
	{
		for (Component* component : components)
		{
			if (typeid(*component).name() == typeid(T).name())
			{
				return (T*)component;
			}
		}
	}

	void log();
};

class Component
{
public:
	bool active = true;
	Entity* owner;

	virtual ~Component();
	virtual void start();
	virtual void update();
	virtual void render();
};
#pragma endregion

#pragma region Components
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

class Renderer : public Component
{
public:
	Color color;

public:
	Renderer();
	~Renderer();
	void render() override;
};

class Collider : public Component
{
public:
	Vector2 position;
	Vector2 offset;
	Color color;
	bool isTrigger;
	Collider* other;

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


class PlayerController : public Component
{
public:
	int speed;
public:
	PlayerController();
	void start() override;
	void update() override;
};
#pragma endregion