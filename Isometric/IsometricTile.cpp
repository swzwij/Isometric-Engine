#include "SFML/Graphics.hpp"
#include "Vector2.h"
#include <iostream>
#include "CoordinateConverter.h"

class IsometricTile
{
public:
	IsometricTile(const sf::Texture& texture, Vector2 position, float height, sf::Color = sf::Color::White)
	{
		_position = CoordinateConverter::WorldToIsometric(position, height);
		_height = height;

		_sprite.setPosition(_position.x, _position.y);
		_sprite.setTexture(texture);
	}

	void Draw(sf::RenderWindow& window)
	{
		window.draw(_sprite);
	}

	void SetSelected(bool selected)
	{
		_sprite.setColor(selected ? sf::Color::Red : sf::Color::White);

		if (selected)
			std::cout << _height << std::endl;
	}

	Vector2 GetPosition() const
	{
		return _position;
	}

	float GetHeight() const
	{
		return _height;
	}

private:
	sf::Sprite _sprite;
	Vector2 _position;
	float _height;
};