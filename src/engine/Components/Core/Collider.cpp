#include "Collider.h"
#include "../../Engine.h"

extern Engine* n_engine;

#pragma region Collider
Collider::Collider()
{
	layer = Layer_Default;
	collisionLayer = Layer_Default;
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
	Component::update();
}

void Collider::notifyComponentsEnter(Collider* collider)
{
	for (Component* component : owner->components)
	{
		component->OnCollisionEnter(collider);
	}
}

void Collider::notifyComponentsStay(Collider* collider)
{
	for (Component* component : owner->components)
	{
		component->OnCollisionStay(collider);
	}
}

void Collider::notifyComponentsExit(Collider* collider)
{
	for (Component* component : owner->components)
	{
		component->OnCollisionExit(collider);
	}
}
#pragma endregion

#pragma region BoxCollider
BoxCollider::BoxCollider()
{
	color = Color::White;
	scale = Vector2(64, 64);
}

bool BoxCollider::isColliding(Collider* collider)
{
	if (aabb_intersect(this, (BoxCollider*)collider)
		&& (collisionLayer & collider->layer) != 0)
	{
		return true;
	}
	return false;
}

void BoxCollider::evaluateCollision(Collider* collider)
{
	Transform* self = owner->transform;
	Transform* other = collider->owner->transform;

	Vector2 diff = self->position - other->position;
	float scaleDiff = (self->scale.y / 2) + (other->scale.y / 2);

	if (abs(diff.y) >= scaleDiff - 2.f)
	{
		if (diff.y > 0)
		{
			collisionFace = Vector2::up;
		}
		else
		{
			collisionFace = Vector2::down;
		}
	}
	else
	{
		if (diff.x > 0)
		{
			collisionFace = Vector2::left;
		}
		else
		{
			collisionFace = Vector2::right;
		}
	}
}

void BoxCollider::update()
{
	Collider::update();
	position = owner->transform->position + offset;
	scale = owner->transform->scale + (Vector2::one * 5.f);

	for (Collider* collider : n_engine->colliders)
	{
		if (collider == this) { continue; }

		if (isColliding(collider))
		{
			if (lastCollider != collider)
			{
				evaluateCollision(collider);
				lastCollider = collider;
				notifyComponentsEnter(collider);
			}
			else
			{
				notifyComponentsStay(collider);
			}
		}
		else
		{
			if (lastCollider == collider)
			{
				notifyComponentsExit(collider);
				lastCollider = nullptr;
			}
		}
	}
}
void BoxCollider::render()
{
	Component::update();
	if (!drawGizmos)
	{
		return;
	}
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
	return (
		a->position.x + (a->scale.x / 2) > b->position.x - (b->scale.x / 2) &&
		b->position.x + (b->scale.x / 2) > a->position.x - (a->scale.x / 2) &&
		a->position.y + (a->scale.y / 2) > b->position.y - (b->scale.y / 2) &&
		b->position.y + (b->scale.y / 2) > a->position.y - (a->scale.y / 2)
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