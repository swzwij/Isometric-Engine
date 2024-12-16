#include "SFML/Graphics.hpp"
#include "Vector2.h"
#include "IsometricTile.cpp"

class World
{
public:
	World(Vector2 worldSize)
	{
		_worldSize = worldSize;

		if (!_tileTexture.loadFromFile("tile.png"))
		{
			std::cout << "Failed to load tile texture" << std::endl;
		}
		else
		{
			std::cout << "Texture loaded successfully" << std::endl;
		}

		for (int x = 0; x < _worldSize.x; x++)
		{
			for (int y = 0; y < _worldSize.y; y++)
			{
				float height = rand() % 3;
				height = rand() % 2 == 0 ? height : -height;
				height /= 10;

				if (y == 0 || y == _worldSize.y - 1 || x == 0 || x == _worldSize.x - 1)
					height = 0;

				_tiles.push_back(IsometricTile(_tileTexture, Vector2(x, y), height));
			}
		}
	}

	void Render(sf::RenderWindow& window)
	{
		for (auto& tile : _tiles)
			tile.Draw(window);
	}

private:
	Vector2 _worldSize;

	sf::Texture _tileTexture;
	std::vector<IsometricTile> _tiles;
};