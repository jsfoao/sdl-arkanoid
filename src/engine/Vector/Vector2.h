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
	Vector2& operator*=(const float& rhs);
	Vector2& operator/=(const float& rhs);

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

	Vector2 GetNormalized() const;
	float Magnitude() const;
	float Distance(const Vector2& v) const;
	static float Dot(const Vector2& v1, const Vector2& v2);
	void print();
};