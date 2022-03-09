#include "ECS.h"
#include <iostream>
#include "../Engine.h"

extern Engine* n_engine;

#pragma region ECS
Entity::Entity()
{
	transform = addComponent<Transform>();
	renderer = addComponent<Renderer>();
}

Entity::~Entity() {}

void Entity::destroy()
{
	active = false;
}

void Entity::start()
{
	for (Component* c : components)
	{
		c->start();
	}
}

void Entity::update()
{
	if (!active) { return; }

	for (Component* c : components)
	{
		c->update();
	}
}

void Entity::render()
{
	if (!active) { return; }

	for (Component* c : components)
	{
		c->render();
	}
}

void Entity::log()
{
	std::cout << "Position: ";
	transform->position.print();
}

Component::~Component() {}
void Component::start() {}
void Component::update() {}
void Component::render() {}
#pragma endregion

#pragma region Components
#pragma region Transform
Transform::~Transform() {}
Transform::Transform()
{
	position = Vector2(0, 0);
	scale = Vector2(32, 32);
}
void Transform::update() {}
#pragma endregion

#pragma region Renderer
Renderer::~Renderer() {}
Renderer::Renderer()
{
	color = Color::White;
}

void Renderer::render()
{
	SDL_SetRenderDrawColor(owner->sdl_renderer, color.r, color.g, color.b, color.a);
	SDL_Rect rect =
	{
		owner->transform->position.x - (owner->transform->scale.x / 2),
		owner->transform->position.y - (owner->transform->scale.y / 2),
		owner->transform->scale.x,
		owner->transform->scale.y
	};
	SDL_RenderFillRect(owner->sdl_renderer, &rect);
}
#pragma endregion

#pragma region PlayerController

PlayerController::PlayerController()
{
	speed = 200;
}

void PlayerController::start()
{
}

void PlayerController::update()
{
	if (n_engine->input->GetKeyDown(SDL_SCANCODE_W))
	{
		owner->transform->position.y -= speed * n_engine->time->deltaTime;
	}
	if (n_engine->input->GetKeyDown(SDL_SCANCODE_S))
	{
		owner->transform->position.y += speed * n_engine->time->deltaTime;
	}
	if (n_engine->input->GetKeyDown(SDL_SCANCODE_A))
	{
		owner->transform->position.x -= speed * n_engine->time->deltaTime;
	}
	if (n_engine->input->GetKeyDown(SDL_SCANCODE_D))
	{
		owner->transform->position.x += speed * n_engine->time->deltaTime;
	}
}
#pragma endregion

#pragma region Collider
Collider::Collider()
{
	isTrigger = false;
	n_engine->colliders.push_back(this);
}

Collider::~Collider()
{
	for (size_t i = 0; i < n_engine->colliders.size(); i++)
	{
		if (n_engine->colliders[i] == this)
		{
			n_engine->colliders.erase(std::next(n_engine->colliders.begin(), i));
		}
	}
}

void Collider::update()
{

}

bool Collider::onCollision()
{
	return isColliding;
}

#pragma endregion

#pragma region BoxCollider
BoxCollider::BoxCollider()
{
	color = Color::White;
	scale = Vector2(64, 64);
}
void BoxCollider::update()
{
	Collider::update();
	position = owner->transform->position + offset;

	for (Collider* collider : n_engine->colliders)
	{
		if (collider == this) { continue; }

		if (aabb_intersect(this, (BoxCollider*)collider))
		{
			isColliding = true;
		}
		else
		{
			isColliding = false;
		}
	}
}
void BoxCollider::render()
{
	SDL_SetRenderDrawColor(owner->sdl_renderer, color.r, color.g, color.b, color.a);
	SDL_Rect rect =
	{
		position.x - (scale.x / 2),
		position.y - (scale.y / 2),
		scale.x,
		scale.y
	};

	SDL_RenderDrawRect(owner->sdl_renderer, &rect);
}
bool aabb_intersect(const BoxCollider* a, const BoxCollider* b)
{
	return
		(
			a->position.x < b->position.x + b->scale.x &&
			a->position.x + a->scale.x > b->position.x &&
			a->position.y < b->position.y + b->scale.y &&
			a->position.y + a->scale.y > b->position.y
			);
}
#pragma endregion

#pragma region CircleCollider
CircleCollider::CircleCollider()
{
	radius = 32;
}
void CircleCollider::update()
{
	Collider::update();
	position = owner->transform->position + offset;
}

const float PI = 3.1415;

void CircleCollider::render()
{
	int resolution = 32;
	float step = (2 * PI) / resolution;

	for (int i = 0; i < resolution; ++i)
	{
		float angle = step * i;
		float x1 = cos(angle);
		float y1 = sin(angle);

		float next_angle = step * (i + 1);
		float x2 = cos(next_angle);
		float y2 = sin(next_angle);

		SDL_RenderDrawLine(
			owner->sdl_renderer,
			x1 * radius + position.x,
			y1 * radius + position.y,
			x2 * radius + position.x,
			y2 * radius + position.y
		);
	}
}

bool circle_intersect(const CircleCollider* a, const CircleCollider* b)
{
	int dx = b->position.x - a->position.x;
	int dy = b->position.y - a->position.y;

	int dist_sqrd = dx * dx + dy * dy;
	int dist = sqrt(dist_sqrd);

	int radius_sum = a->radius + b->radius;
	return dist < radius_sum;
}

int clamp(int a, int min, int max)
{
	if (a < min)
		return min;
	if (a > max)
		return max;

	return a;
}

bool aabb_circle_intersect(const BoxCollider* box, const CircleCollider* circle)
{
	float xMin = box->position.x - (box->scale.x / 2);
	float xMax = box->position.x + (box->scale.x / 2);
	float yMin = box->position.y - (box->scale.y / 2);
	float yMax = box->position.y + (box->scale.y / 2);

	float clamped_x = clamp(circle->position.x, xMin, xMax);
	float clamped_y = clamp(circle->position.y, yMin, yMax);

	float dx = circle->position.x - clamped_x;
	float dy = circle->position.y - clamped_y;

	float dist_sqrd = dx * dx + dy * dy;
	float dist = sqrt(dist_sqrd);

	return dist < circle->radius;
}
#pragma endregion

#pragma endregion