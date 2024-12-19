#include "PerlinNoise.h"
#include "IsometricTile.cpp"

class WorldGeneration
{
public:
	void SetSeed(int seed) { _noise = PerlinNoise(seed); }

	void RandomizeSeed() { _noise = PerlinNoise(); }

	IsometricTile GenerateTile(int x, int y)
	{
		float tileHeight = CalculateTileHeight(x, y);

		// Get Texture

		IsometricTile tile = IsometricTile
		(
			texture,
			Vector2(x, y),
			tileHeight
		);
	}

private:
	PerlinNoise _noise;
	float _noiseScale = 0.05;
	int _noiseOctaves = 4;
	float _noisePersistence = 0.2;
	float _noiseMultiplier = 7.5;

	float CalculateTileHeight(int x, int y)
	{
		float height = _noise.octaveNoise
		(
			x * _noiseScale,
			y * _noiseScale,
			0.0,
			_noiseOctaves,
			_noisePersistence
		);

		height *= _noiseMultiplier;
		height = round(height * 2) / 2;

		return height;
	}
};