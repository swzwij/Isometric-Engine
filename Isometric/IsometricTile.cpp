#include "SFML/Graphics.hpp"
#include "Vector2.h"
#include <iostream>

class IsometricTile
{
public:
	IsometricTile(const sf::Texture& texture, Vector2 position, float height, sf::Color = sf::Color::White)
	{
		float tileWidth = 256.0f;
		float tileHeight = 128.0f;

		Vector2 isometricPosition = Vector2
		(
			(position.x - position.y) * (tileWidth / 2),
			(position.x + position.y) * (tileHeight / 2) - (height * tileHeight / 2)
		);

		_position = position;

		_sprite.setPosition(isometricPosition.x, isometricPosition.y);
		_sprite.setTexture(texture);
	}

	void Draw(sf::RenderWindow& window)
	{
		window.draw(_sprite);
	}

	void SetSelected(bool selected)
	{
		_sprite.setColor(selected ? sf::Color::Red : sf::Color::White);
	}

	Vector2 GetPosition() const
	{
		return _position;
	}

	static Vector2 WorldToIsometric(const Vector2& worldPosition, float tileWidth = 256.0f, float tileHeight = 128.0f)
	{
		float halfWidth = tileWidth / 2.0f;
		float halfHeight = tileHeight / 2.0f;

		//float adjustedWorldY = worldPosition.y + (_selectedTile ? _selectedTile->GetHeight() * halfHeight : 0);

		float isoX = (worldPosition.x / halfWidth + worldPosition.y / halfHeight) / 2.0f;
		float isoY = (worldPosition.y / halfHeight - worldPosition.x / halfWidth) / 2.0f;

		return Vector2
		(
			std::round(isoX),
			std::round(isoY)
		);
	}

private:
	sf::Sprite _sprite;
	Vector2 _position;
};