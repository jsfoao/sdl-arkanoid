#pragma once
struct Vector2
{
	int x, y;

	Vector2();
	~Vector2();

	Vector2(float newX, float newY);

	Vector2& operator=(const Vector2& rhs);
	Vector2& operator+=(const Vector2& rhs);
	Vector2& operator-=(const Vector2& rhs);
	Vector2& operator*=(const int& rhs);

	friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
	{
		Vector2 temp;
		temp.x = lhs.x + rhs.x;
		temp.y = lhs.y + rhs.y;
		return temp;
	}
	friend Vector2 operator-(Vector2& lhs, const Vector2& rhs)
	{
		Vector2 temp;
		temp.x = lhs.x - rhs.x;
		temp.y = lhs.y - rhs.y;
		return temp;
	}
	friend Vector2 operator*(const Vector2& lhs, const int& rhs)
	{
		Vector2 temp;
		temp.x = lhs.x * rhs;
		temp.y = lhs.y * rhs;
		return temp;
	}

	void print();
};