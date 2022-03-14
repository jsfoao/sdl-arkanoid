#include "Rigidbody.h"

void Rigidbody::update()
{
	owner->transform->position += velocity;
}