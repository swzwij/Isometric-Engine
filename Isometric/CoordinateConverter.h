#pragma once
#include "Vector2.h"

class CoordinateConverter {
public:
    static Vector2 WorldToIsometric(const Vector2& worldPos, float height = 0.0f, float tileWidth = 256.0f, float tileHeight = 128.0f);
    static Vector2 IsometricToWorld(const Vector2& isoPos, float height = 0.0f, float tileWidth = 256.0f, float tileHeight = 128.0f);
};