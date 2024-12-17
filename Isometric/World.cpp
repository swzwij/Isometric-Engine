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

		_grassTileTexture.loadFromFile("grassTile.png");
		_waterTileTexture.loadFromFile("waterTile.png");
		_stoneTileTexture.loadFromFile("stoneTile.png");
		_sandTileTexture.loadFromFile("sandTile.png");

		Setup();
	}

	void Setup()
	{
		_tiles.clear();

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

				sf::Texture texture = height < -1 
					? _waterTileTexture 
					: height >= -1 && height < -0.75 
					? _sandTileTexture 
					: height >= -0.75 && height < 1.5 
					? _grassTileTexture 
					: _stoneTileTexture;

				_tiles.push_back(IsometricTile
				(
					texture,
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

	sf::Texture _grassTileTexture;
	sf::Texture _waterTileTexture;
	sf::Texture _stoneTileTexture;
	sf::Texture _sandTileTexture;

	std::vector<IsometricTile> _tiles;
};