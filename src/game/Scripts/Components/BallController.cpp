#include "BallController.h"
#include "../src/engine/Engine.h"

extern Engine* n_engine;
extern Entity* player;

void BallController::start()
{
	rb = owner->getComponent<Rigidbody>();
	boxCollider = owner->getComponent<BoxCollider>();
	direction = Vector2::down;
	speed = 200.f;
	angleFactor = 2.f;
	damage = 1;
}
void BallController::update()
{
	if (Input::GetKeyDown(SDL_SCANCODE_SPACE) && holding == true)
	{
		std::cout << "space" << std::endl;
		direction = Vector2::up;
		holding = false;
	}

	if (holding)
	{
		owner->transform->position = player->transform->position + Vector2(0.f, -20.f);
		return;
	}
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

	if (collider->layer == Layer_Brick)
	{
		collider->owner->getComponent<BrickController>()->Damage(damage);
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