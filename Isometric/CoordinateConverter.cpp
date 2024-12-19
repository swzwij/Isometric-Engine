#include "CoordinateConverter.h"
#include <cmath>

Vector2 CoordinateConverter::WorldToIsometric(const Vector2& worldPos, float height, float tileWidth, float tileHeight)
{
    float halfWidth = tileWidth / 2.0f;
    float halfHeight = tileHeight / 2.0f;

    float isoX = (worldPos.x - worldPos.y) * halfWidth;
    float isoY = (worldPos.x + worldPos.y) * halfHeight - (height * tileHeight);

    return Vector2(isoX, isoY);
}

Vector2 CoordinateConverter::IsometricToWorld(const Vector2& isoPos, float height, float tileWidth, float tileHeight)
{
    float halfWidth = tileWidth / 2.0f;
    float halfHeight = tileHeight / 2.0f;

    float adjustedIsoY = isoPos.y + (height * tileHeight);

    float worldX = (isoPos.x / halfWidth + adjustedIsoY / halfHeight) / 2.0f;
    float worldY = (adjustedIsoY / halfHeight - isoPos.x / halfWidth) / 2.0f;

    return Vector2(std::round(worldX), std::round(worldY));
}