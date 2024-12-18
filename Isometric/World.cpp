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
		GenerateTiles();
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
	std::vector<float> _heights;

	float _noiseScale = 0.05;
	int _noiseOctaves = 4;
	float _noisePersistence = 0.2;

	int _waterHeight = -1;
	int _sandHeight = -0.5;
	int _grassHeight = 0;
	int _stoneHeight = 2;

	void GenerateTiles()
	{
		PerlinNoise noise;

		_tiles.clear();

		for (int x = 0; x < _worldSize.x; x++)
		{
			for (int y = 0; y < _worldSize.y; y++)
			{
				float height = noise.octaveNoise
				(
					x * _noiseScale,
					y * _noiseScale,
					0.0,
					_noiseOctaves,
					_noisePersistence
				) * 7.5;

				height = round(height * 2) / 2;

				sf::Texture texture = GetTileTexture(height);

				if (height < _waterHeight)
					height = _waterHeight;

				_tiles.push_back(IsometricTile
				(
					texture,
					Vector2(x, y),
					height
				));

				_heights.push_back(height);
			}
		}
	}

	sf::Texture GetTileTexture(float height)
	{
		return height <= _waterHeight
			? _waterTileTexture
			: height > _waterHeight && height <= _sandHeight && height < _grassHeight
			? _sandTileTexture
			: height > _stoneHeight
			? _stoneTileTexture
			: _grassTileTexture;
	}
};