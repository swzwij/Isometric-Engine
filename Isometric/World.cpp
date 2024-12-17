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

		if(!_grassTileTexture.loadFromFile("grassTile.png"))
			std::cout << "Failed to load grassTile.png" << std::endl;

		if (!_waterTileTexture.loadFromFile("waterTile.png"))
			std::cout << "Failed to load waterTile.png" << std::endl;

		if (!_stoneTileTexture.loadFromFile("stoneTile.png"))
			std::cout << "Failed to load stoneTile.png" << std::endl;

		if(!_sandTileTexture.loadFromFile("sandTile.png"))
			std::cout << "Failed to load sandTile.png" << std::endl;

		Setup();
	}

	void Setup()
	{
		_tiles.clear();

		float scale = .1;
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
					: height >= -1 && height < -0.5 
					? _sandTileTexture 
					: height > 2 
					?  _stoneTileTexture
					: _grassTileTexture;

				if (height < -1)
					height = -1;

				height = 0;

				_tiles.push_back(IsometricTile
				(
					texture,
					Vector2(x, y),
					height
				));
			}
		}
	}

	IsometricTile* GetTileAt(Vector2 position)
	{
		if (position.x < 0 || position.x >= _worldSize.x || position.y < 0 || position.y >= _worldSize.y)
			return nullptr;

		int index = position.y + (position.x - 1) * _worldSize.y;

		return &_tiles[index];
	}

	void Render(sf::RenderWindow& window)
	{
		for (auto& tile : _tiles)
			tile.Draw(window);
	}

	Vector2 GetWorldSize() const
	{
		return _worldSize;
	}

private:
	Vector2 _worldSize;

	sf::Texture _grassTileTexture;
	sf::Texture _waterTileTexture;
	sf::Texture _stoneTileTexture;
	sf::Texture _sandTileTexture;

	std::vector<IsometricTile> _tiles;
};