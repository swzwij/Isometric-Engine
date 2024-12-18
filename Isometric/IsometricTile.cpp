#include "SFML/Graphics.hpp"
#include "Vector2.h"
#include <iostream>

class IsometricTile
{
public:
	IsometricTile(const sf::Texture& texture, Vector2 position, float height)
	{
		_position = position;
		_height = height;
		_texture = texture;
		_sprite.setTexture(texture);

		float tileWidth = _sprite.getLocalBounds().width;
		float tileHeight = _sprite.getLocalBounds().height;

		tileHeight = tileHeight == tileWidth ? tileHeight / 2 : tileHeight;

		Vector2 isometricPosition = Vector2
		(
			(position.x - position.y) * (tileWidth / 2),
			(position.x + position.y) * (tileHeight / 2) - (height * tileHeight / 2)
		);

		_sprite.setPosition(isometricPosition.x, isometricPosition.y);
	}

	void Draw(sf::RenderWindow& window)
	{
		_sprite.setTexture(_texture);
		window.draw(_sprite);
	}

	void SetSelected(bool selected)
	{
		_sprite.setColor(selected ? sf::Color::Red : sf::Color::White);
	}

	float GetHeight() const { return _height; }
	Vector2 GetPosition() const { return _position; }

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
	sf::Texture _texture;
	sf::Sprite _sprite;
	float _height;
	Vector2 _position;
};