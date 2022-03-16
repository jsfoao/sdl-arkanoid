#include "Vector2.h"
#include <iostream>

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::~Vector2(){}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2& Vector2::operator=(const Vector2& rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vector2& Vector2::operator*=(const float& rhs)
{
	x *= rhs;
	y *= rhs;
	return *this;
}

Vector2& Vector2::operator/=(const float& rhs)
{
	x /= rhs;
	y /= rhs;
	return *this;
}

float Vector2::Magnitude() const
{
	return sqrt(x * x + y * y);
}

Vector2 Vector2::GetNormalized() const
{
	float magnitude = Magnitude();
	return Vector2(x / magnitude, y / magnitude);
}

float Vector2::Distance(const Vector2& v) const
{
	Vector2 diff = *this - v;
	return diff.Magnitude();
}

float Vector2::Dot(const Vector2& v1, const Vector2& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y);
}

void Vector2::print()
{
	std::cout << "(" << x << "," << y << ")" << std::endl;
}


const Vector2 Vector2::zero = Vector2(0, 0);
const Vector2 Vector2::one = Vector2(1, 1);
const Vector2 Vector2::up = Vector2(0, -1);
const Vector2 Vector2::down = Vector2(0, 1);
const Vector2 Vector2::right = Vector2(1, 0);
const Vector2 Vector2::left = Vector2(-1, 0);