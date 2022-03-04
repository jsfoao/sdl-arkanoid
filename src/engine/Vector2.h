#pragma once
struct Vector2
{
	int x, y;

	Vector2();
	~Vector2();

	Vector2(int newX, int newY);

	Vector2& operator+=(const Vector2& rhs);
	Vector2& operator-=(const Vector2& rhs);
	void print();
};