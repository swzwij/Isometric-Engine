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

		_grassTileTexture = std::make_shared<sf::Texture>();
		_waterTileTexture = std::make_shared<sf::Texture>();
		_stoneTileTexture = std::make_shared<sf::Texture>();
		_sandTileTexture = std::make_shared<sf::Texture>();
		_transparentWaterTexture = std::make_shared<sf::Texture>();

		const std::string imagePath = "Assets/Images/";

		if (!_grassTileTexture->loadFromFile(imagePath + "grassTile.png"))
			std::cout << "Failed to load grassTile.png" << std::endl;

		if (!_waterTileTexture->loadFromFile(imagePath + "waterTile.png"))
			std::cout << "Failed to load waterTile.png" << std::endl;

		if (!_stoneTileTexture->loadFromFile(imagePath + "stoneTile.png"))
			std::cout << "Failed to load stoneTile.png" << std::endl;

		if (!_sandTileTexture->loadFromFile(imagePath + "sandTile.png"))
			std::cout << "Failed to load sandTile.png" << std::endl;

		if (!_transparentWaterTexture->loadFromFile(imagePath + "transparentWaterTile.png"))
			std::cout << "Failed to load transparentWater.png" << std::endl;

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

		IsometricTile* tile = &_tiles[index];

		float height = tile->GetHeight();

		return tile;
	}

	void Render(sf::RenderWindow& window, sf::View& view)
	{
		for (IsometricTile& tile : _tiles)
			if (IsTileInView(tile.GetPosition(), view))
				tile.Draw(window);

		for (IsometricTile& waterTile : _waterTiles)
			if (IsTileInView(waterTile.GetPosition(), view))
				waterTile.Draw(window);
	}

	bool IsTileInView(Vector2 tilePosition, sf::View& view)
	{
		sf::Vector2f viewCenter = view.getCenter();
		sf::Vector2f viewSize = view.getSize();

		if (tilePosition.x > viewCenter.x + viewSize.x || tilePosition.x < viewCenter.x - viewSize.x)
			return false;

		if (tilePosition.y < viewCenter.y - viewSize.y || tilePosition.y > viewCenter.y + viewSize.y)
			return false;

		return true;
	}

	Vector2 GetWorldSize() const
	{
		return _worldSize;
	}

	void AddTile(IsometricTile tile)
	{
		_tiles.push_back(tile);
	}

private:
	Vector2 _worldSize;

	std::shared_ptr<sf::Texture> _grassTileTexture;
	std::shared_ptr<sf::Texture> _waterTileTexture;
	std::shared_ptr<sf::Texture> _stoneTileTexture;
	std::shared_ptr<sf::Texture> _sandTileTexture;
	std::shared_ptr<sf::Texture> _transparentWaterTexture;

	std::vector<IsometricTile> _tiles;
	std::vector<IsometricTile> _waterTiles;
	std::vector<float> _heights;

	int _waterHeight = -1;
	int _sandHeight = -0.5;
	int _grassHeight = 0;
	int _stoneHeight = 2;

	float _noiseScale = 0.05;
	int _noiseOctaves = 4;
	float _noisePersistence = 0.2;

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

				const sf::Texture& texture = *GetTileTexture(height);


				IsometricTile tile = IsometricTile
				(
					texture,
					Vector2(x, y),
					height
				);

				_tiles.push_back(tile);
				_heights.push_back(height);

				if (height <= -1)
				{
					IsometricTile waterTile = IsometricTile
					(
						*_transparentWaterTexture,
						Vector2(x, y),
						_waterHeight + 0.5f,
						sf::Color(255, 255, 255, 255)
					);

					_waterTiles.push_back(waterTile);
				}
			}
		}
	}

	std::shared_ptr<sf::Texture> GetTileTexture(float height)
	{
		return height <= _sandHeight && height < _grassHeight
			? _sandTileTexture
			: height > _stoneHeight
			? _stoneTileTexture
			: _grassTileTexture;
	}
};