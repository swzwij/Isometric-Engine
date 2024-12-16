#include "SFML/Graphics.hpp"
#include "Vector2.h"
#include <iostream>

class IsometricTile
{
public:
	IsometricTile(const sf::Texture& texture, Vector2 position, float height)
	{
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
		window.draw(_sprite);
	}

private:
	sf::Sprite _sprite;
};