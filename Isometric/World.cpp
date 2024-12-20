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
		_worldGeneration.RandomizeSeed();
		GenerateTiles();
		CalculateLighting();
	}

	IsometricTile* GetTileAt(Vector2 position)
	{
		if (position.x < 0 || position.x >= _worldSize.x || position.y < 0 || position.y >= _worldSize.y)
			return nullptr;

		int index = position.y + position.x * _worldSize.y;

		IsometricTile* tile = &_tiles[index];

		float height = tile->GetHeight();

		return tile;
	}

	void Render(sf::RenderWindow& window, sf::View& view)
	{
		//SortTiles();

		for (IsometricTile& tile : _tiles)
			if (IsTileInView(tile.GetPosition(), view))
				tile.Draw(window);

		for (IsometricTile& waterTile : _waterTiles)
			if (IsTileInView(waterTile.GetPosition(), view))
				waterTile.Draw(window);
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

		_waterTiles.push_back(waterTile);
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

	void CalculateLighting()
	{
		Vector2 lightDir(1,0);
		float lightIntensity = 1.0f;

		for (int x = 0; x < _worldSize.x; x++)
		{
			for (int y = 0; y < _worldSize.y; y++)
			{
				IsometricTile* currentTile = GetTileAt(Vector2(x, y));
				if (!currentTile)
					continue;

				float c = currentTile->GetHeight(); // center
				float l = GetHeightAt(x - 1, y);    // left
				float r = GetHeightAt(x + 1, y);    // right
				float t = GetHeightAt(x, y - 1);    // top
				float b = GetHeightAt(x, y + 1);    // bottom
				float tl = GetHeightAt(x - 1, y - 1); // top-left
				float tr = GetHeightAt(x + 1, y - 1); // top-right
				float bl = GetHeightAt(x - 1, y + 1); // bottom-left
				float br = GetHeightAt(x + 1, y + 1); // bottom-right

				float dx = ((tr + 2.0f * r + br) - (tl + 2.0f * l + bl)) / 8.0f;
				float dy = ((bl + 2.0f * b + br) - (tl + 2.0f * t + tr)) / 8.0f;

				Vector2 normal;
				normal.x = -dx;
				normal.y = -dy;

				float z = 1.0f;

				float length = sqrt(normal.x * normal.x + normal.y * normal.y + z * z);
				if (length > 0.0f)
				{
					normal.x /= length;
					normal.y /= length;
					z /= length;
				}

				float dotProduct = normal.x * lightDir.x + normal.y * lightDir.y + z * 0.5f;

				float lightLevel = 0.5f + (dotProduct * 0.5f);

				float aoFactor = 1.0f;
				std::vector<float> heightDiffs = 
				{
					c - l, c - r, c - t, c - b,
					c - tl, c - tr, c - bl, c - br
				};

				float avgHeightDiff = 0.0f;
				int validNeighbors = 0;

				for (float diff : heightDiffs)
				{
					if (diff > 0)
					{
						avgHeightDiff += diff;
						validNeighbors++;
					}
				}

				if (validNeighbors > 0)
				{
					avgHeightDiff /= validNeighbors;
					aoFactor = 1.0f - (avgHeightDiff * 0.15f);
					aoFactor = std::max(0.6f, aoFactor);
				}

				float edgeFactor = 1.0f;
				if (abs(dx) > 0.5f || abs(dy) > 0.5f)
				{
					edgeFactor = 1.1f;
				}

				float finalLight = lightLevel * aoFactor * lightIntensity * edgeFactor;

				finalLight = std::max(0.0f, std::min(1.0f, finalLight));

				currentTile->SetLightLevel(finalLight);
			}
		}
	}

	float GetHeightAt(int x, int y) 
	{
		if (x < 0 || x >= _worldSize.x || y < 0 || y >= _worldSize.y)
			return 0.0f;

		IsometricTile* tile = GetTileAt(Vector2(x, y));
		return tile ? tile->GetHeight() : 0.0f;
	}
};