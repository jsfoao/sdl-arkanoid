#include "BallController.h"
#include "../src/engine/Engine.h"

static Rigidbody* rb;
static Vector2 direction;
static BoxCollider* boxCollider;

extern Engine* n_engine;
void BallController::start()
{
	rb = owner->getComponent<Rigidbody>();
	boxCollider = owner->getComponent<BoxCollider>();
	direction = Vector2::up;
	speed = 200.f;
	angleFactor = 2.f;
	damage = 1;
}
void BallController::update()
{
	rb->velocity = direction.GetNormalized() * speed;
	WindowCollision();
}

void BallController::OnCollisionEnter(Collider* collider)
{
	if (boxCollider->collisionFace == Vector2::down)
	{
		direction.y = -1;
	}
	else if (boxCollider->collisionFace == Vector2::up)
	{
		direction.y = 1;
	}

	else if (boxCollider->collisionFace == Vector2::right)
	{
		direction.x = -1;
	}
	else if (boxCollider->collisionFace == Vector2::left)
	{
		direction.x = 1;
	}

	Transform* colTransform = collider->owner->transform;
	float widthX = colTransform->position.x - owner->transform->position.x;

	// player hits
	if (collider->layer == Layer_Player)
	{
		direction.x = - (widthX / collider->owner->getComponent<PlayerController>()->width) * angleFactor;
	}
}

void BallController::WindowCollision()
{
	if (owner->transform->position.y + (owner->transform->scale.y / 2) >= n_engine->window->height)
	{
		direction.y = -1;
	}
	else if (owner->transform->position.y - (owner->transform->scale.y / 2) <= 0)
	{
		direction.y = 1;
	}
	else if (owner->transform->position.x + (owner->transform->scale.x / 2) >= n_engine->window->width)
	{
		direction.x = -1;
	}
	else if (owner->transform->position.x - (owner->transform->scale.x / 2) <= 0)
	{
		direction.x = 1;
	}
}