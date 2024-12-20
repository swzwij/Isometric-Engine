#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

struct Vector3
{
	float x, y, z;

	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	Vector3 operator+(const Vector3& v) const;
	Vector3 operator-(const Vector3& v) const;
	Vector3 operator*(float scalar) const;
	Vector3 operator/(float scalar) const;

	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(float scalar);
	Vector3& operator/=(float scalar);

	bool operator==(const Vector3& v) const;
	bool operator!=(const Vector3& v) const;

	float Magnitude() const;
	Vector3 Normalized() const;
	float Dot(const Vector3& v) const;
};

#endif // !VECTOR3_H
