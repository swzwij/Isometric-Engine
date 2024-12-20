#include <cmath>

struct Vector3
{
	float x, y, z;

	Vector3() : x(0.0f), y(0.0f), z(0.0f) { }
	Vector3(float x, float y, float z) : x(x), y(y), z(z) { }

	Vector3 operator+(const Vector3& v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator-(const Vector3& v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 operator*(float scalar) const
	{
		return Vector3(x * scalar, y * scalar, z * scalar);
	}

	Vector3 operator/(float scalar) const
	{
		return Vector3(x / scalar, y / scalar, z / scalar);
	}

	Vector3& operator+=(const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vector3& operator-=(const Vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vector3& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	Vector3& operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

	bool operator==(const Vector3& v) const
	{
		return x == v.x && y == v.y && z == v.z;
	}

	bool operator!=(const Vector3& v) const
	{
		return !(*this == v);
	}

	float Magnitude() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	Vector3 Normalized() const
	{
		float mag = Magnitude();
		return Vector3(x / mag, y / mag, z / mag);
	}

	float Dot(const Vector3& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}
};