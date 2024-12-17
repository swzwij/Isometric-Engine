#include "SFML/Graphics.hpp"
#include "Vector2.h"
#include "IsometricTile.cpp"
#include "PerlinNoise.h"

class World
{
public:
	World(Vector2 worldSize)
	{
		_worldSize = worldSize;

		_tileTexture.loadFromFile("tile.png");

		float scale = 0.1;
		int octaves = 4;
		float persistence = 0.4;

		PerlinNoise noise;

		for (int x = 0; x < _worldSize.x; x++)
		{
			for (int y = 0; y < _worldSize.y; y++)
			{
				float height = noise.octaveNoise
				(
					x * scale,
					y * scale,
					0.0, 
					octaves,
					persistence
				) * 5;

				_tiles.push_back(IsometricTile
				(
					_tileTexture,
					Vector2(x, y),
					height
				));
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