#include "SFML/Graphics.hpp"
#include "Vector2.h"
#include "IsometricTile.cpp"
#include "PerlinNoise.h"
#include "WorldGeneration.cpp"

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
		SortTiles();

		for (IsometricTile& tile : _tiles)
			if (IsTileInView(tile.GetPosition(), view))
				tile.Draw(window);

		//for (IsometricTile& waterTile : _waterTiles)
		//	if (IsTileInView(waterTile.GetPosition(), view))
		//		waterTile.Draw(window);
	}

	Vector2 GetWorldSize() const { return _worldSize; }

private:
	Vector2 _worldSize;

	std::shared_ptr<sf::Texture> _grassTileTexture;
	std::shared_ptr<sf::Texture> _waterTileTexture;
	std::shared_ptr<sf::Texture> _stoneTileTexture;
	std::shared_ptr<sf::Texture> _sandTileTexture;
	std::shared_ptr<sf::Texture> _transparentWaterTexture;

	std::vector<IsometricTile> _tiles;
	std::vector<IsometricTile> _waterTiles;

	WorldGeneration _worldGeneration;

	void GenerateTiles()
	{
		PerlinNoise noise;

		_tiles.clear();
		_tiles.reserve(_worldSize.x * _worldSize.y * 2);

		for (int x = 0; x < _worldSize.x; x++)
		{
			for (int y = 0; y < _worldSize.y; y++)
			{
				if (CreateGroundTile(x, y) > _worldGeneration.GetWaterHeight())
					continue;

				CreateWaterTile(x, y);
			}
		}
	}

	float CreateGroundTile(int x, int y)
	{
		float height = _worldGeneration.CalculateTileHeight(x, y);

		IsometricTile tile = IsometricTile
		(
			*GetTileTexture(height),
			Vector2(x, y),
			height
		);

		_tiles.push_back(tile);

		return height;
	}

	void CreateWaterTile(int x, int y)
	{
		IsometricTile waterTile = IsometricTile
		(
			*_transparentWaterTexture,
			Vector2(x, y),
			_worldGeneration.GetWaterHeight() + 0.5f,
			sf::Color(255, 255, 255, 255)
		);

		_tiles.push_back(waterTile);
	}

	std::shared_ptr<sf::Texture> GetTileTexture(float height)
	{
		return height <= _worldGeneration.GetSandHeight() && height < _worldGeneration.GetGrassHeight()
			? _sandTileTexture
			: height > _worldGeneration.GetStoneHeight()
			? _stoneTileTexture
			: _grassTileTexture;
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

	void SortTiles()
	{
		std::sort(_tiles.begin(), _tiles.end(), [](IsometricTile& a, IsometricTile& b)
		{
			if (a.GetPosition().y != b.GetPosition().y)
				return a.GetPosition().y < b.GetPosition().y;

			if (a.GetPosition().x != b.GetPosition().x)
				return a.GetPosition().x < b.GetPosition().x;

			return a.GetHeight() < b.GetHeight();
		});
	}
};