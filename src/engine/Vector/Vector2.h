#pragma once
struct Vector2
{
	float x, y;

	Vector2();
	~Vector2();

	Vector2(float newX, float newY);

	Vector2& operator=(const Vector2& rhs);
	Vector2& operator+=(const Vector2& rhs);
	Vector2& operator-=(const Vector2& rhs);
	Vector2& operator*=(const float& rhs);
	Vector2& operator/=(const float& rhs);

	friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
	{
		Vector2 temp;
		temp.x = lhs.x + rhs.x;
		temp.y = lhs.y + rhs.y;
		return temp;
	}
	friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
	{
		Vector2 temp;
		temp.x = lhs.x - rhs.x;
		temp.y = lhs.y - rhs.y;
		return temp;
	}
	friend Vector2 operator*(const Vector2& lhs, const float& rhs)
	{
		Vector2 temp;
		temp.x = lhs.x * rhs;
		temp.y = lhs.y * rhs;
		return temp;
	}

	friend Vector2 operator/(const Vector2& lhs, const float& rhs)
	{
		Vector2 temp;
		temp.x = lhs.x / rhs;
		temp.y = lhs.y / rhs;
		return temp;
	}

	friend bool operator==(const Vector2& lhs, const Vector2& rhs)
	{
		return (lhs.x == rhs.x && lhs.y == rhs.y);
	}

	Vector2 GetNormalized() const;
	float Magnitude() const;
	float Distance(const Vector2& v) const;
	static float Dot(const Vector2& v1, const Vector2& v2);
	void print();

	const static Vector2 zero;
	const static Vector2 one;
	const static Vector2 up;
	const static Vector2 down;
	const static Vector2 right;
	const static Vector2 left;
};