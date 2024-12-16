#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>
#include <SFML/Graphics.hpp>

struct Vector2
{
    float x;
    float y;

    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float x, float y) : x(x), y(y) {}

    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(float scalar) const;
    Vector2 operator/(float scalar) const;

    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);
    Vector2& operator*=(float scalar);
    Vector2& operator/=(float scalar);

    float Magnitude() const;
    Vector2 Normalized() const;

    static float Dot(const Vector2& a, const Vector2& b);
    static Vector2 Zero();
    static Vector2 Up();
    static Vector2 Down();
    static Vector2 Left();
    static Vector2 Right();
    static Vector2 One();

    sf::Vector2f ToSFML() const;
};

#endif