#include "PerlinNoise.h"

class WorldGeneration
{
public:
	WorldGeneration() { RandomizeSeed(); }

	void SetSeed(int seed) { _noise = PerlinNoise(seed); }

	void RandomizeSeed() { _noise = PerlinNoise(); }

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

	float GetWaterHeight() { return _waterHeight; }
	float GetSandHeight() { return _sandHeight; }
	float GetGrassHeight() { return _grassHeight; }
	float GetStoneHeight() { return _stoneHeight; }

private:
	PerlinNoise _noise;
	float _noiseScale = 0.05;
	int _noiseOctaves = 4;
	float _noisePersistence = 0.2;
	float _noiseMultiplier = 7.5;

	int _waterHeight = -1;
	int _sandHeight = -0.5;
	int _grassHeight = 0;
	int _stoneHeight = 2;
};