#include "Vector2.h"
#include <iostream>

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::~Vector2(){}

Vector2::Vector2(int newX, int newY)
{
	x = newX;
	y = newY;
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

Vector2& Vector2::operator*=(const int& rhs)
{
	x *= rhs;
	y *= rhs;
	return *this;
}

void Vector2::print()
{
	std::cout << "(" << x << "," << y << ")" << std::endl;
}