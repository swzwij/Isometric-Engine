#include "SFML/Graphics.hpp"
#include "Vector2.h"
#include <iostream>

class IsometricTile
{
public:
	IsometricTile(const sf::Texture& texture, Vector2 position, float height)
	{
		_height = height;
		_texture = texture;
		_sprite.setTexture(_texture);

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

	float GetHeight() const
	{
		return _height;
	}

private:
	sf::Texture _texture;
	sf::Sprite _sprite;
	float _height;
};