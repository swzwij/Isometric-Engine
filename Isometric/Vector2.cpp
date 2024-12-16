#include <cmath>
#include <SFML/Graphics.hpp>

struct Vector2
{
	float x;
	float y;

	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(float x, float y) : x(x), y(y) {}

	Vector2 operator+(const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator-(const Vector2& other) const
	{
		return Vector2(x - other.x, y - other.y);
	}

	Vector2 operator*(float scalar) const
	{
		return Vector2(x * scalar, y * scalar);
	}

	Vector2 operator/(float scalar) const
	{
		return Vector2(x / scalar, y / scalar);
	}

	Vector2& operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2& operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vector2& operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}

	float Magnitude() const
	{
		return sqrt(x * x + y * y);
	}

	Vector2 Normalized() const
	{
		float magnitude = Magnitude();
		return Vector2(x / magnitude, y / magnitude);
	}

	static float Dot(const Vector2& a, const Vector2& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	static Vector2 Zero()
	{
		return Vector2(0.0f, 0.0f);
	}

	static Vector2 Up()
	{
		return Vector2(0.0f, 1.0f);
	}

	static Vector2 Down()
	{
		return Vector2(0.0f, -1.0f);
	}

	static Vector2 Left()
	{
		return Vector2(-1.0f, 0.0f);
	}

	static Vector2 Right()
	{
		return Vector2(1.0f, 0.0f);
	}

	static Vector2 One()
	{
		return Vector2(1.0f, 1.0f);
	}

	sf::Vector2f ToSFML() const
	{
		return sf::Vector2f(x, y);
	}
};