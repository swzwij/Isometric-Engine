#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H

#include <vector>
#include <cmath>
#include <random>
#include <numeric>

class PerlinNoise {
private:
    // Permutation vector
    std::vector<int> p;

    // Dot product of gradient and distance vector
    double dot(int h, double x, double y, double z) {
        switch (h & 15) {
        case  0: return  x + y;
        case  1: return -x + y;
        case  2: return  x - y;
        case  3: return -x - y;
        case  4: return  x + z;
        case  5: return -x + z;
        case  6: return  x - z;
        case  7: return -x - z;
        case  8: return  y + z;
        case  9: return -y + z;
        case 10: return  y - z;
        case 11: return -y - z;
        case 12: return  y + x;
        case 13: return -y + z;
        case 14: return  y - x;
        case 15: return -y - z;
        default: return 0; // Never happens
        }
    }

    // Fade function as defined by Ken Perlin
    double fade(double t) {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    // Linear interpolation
    double lerp(double t, double a, double b) {
        return a + t * (b - a);
    }

public:
    // Constructor with optional seed
    PerlinNoise(unsigned int seed = std::random_device{}()) {
        p.resize(512);
        std::vector<int> permutation(256);

        // Generate initial permutation
        std::mt19937 generator(seed);
        std::iota(permutation.begin(), permutation.end(), 0);
        std::shuffle(permutation.begin(), permutation.end(), generator);

        // Duplicate the permutation to avoid overflow
        for (int i = 0; i < 256; i++) {
            p[i] = permutation[i];
            p[i + 256] = permutation[i];
        }
    }

    // 3D Perlin noise
    double noise(double x, double y, double z) {
        // Find unit cube that contains point
        int X = static_cast<int>(std::floor(x)) & 255;
        int Y = static_cast<int>(std::floor(y)) & 255;
        int Z = static_cast<int>(std::floor(z)) & 255;

        // Relative xyz in the cube
        x -= std::floor(x);
        y -= std::floor(y);
        z -= std::floor(z);

        // Compute fade curves for xyz
        double u = fade(x);
        double v = fade(y);
        double w = fade(z);

        // Hash coordinates of the 8 cube corners
        int A = p[X] + Y;
        int AA = p[A] + Z;
        int AB = p[A + 1] + Z;
        int B = p[X + 1] + Y;
        int BA = p[B] + Z;
        int BB = p[B + 1] + Z;

        // Blend results from 8 corners
        return lerp(w,
            lerp(v,
                lerp(u, dot(p[AA], x, y, z),
                    dot(p[BA], x - 1, y, z)),
                lerp(u, dot(p[AB], x, y - 1, z),
                    dot(p[BB], x - 1, y - 1, z))),
            lerp(v,
                lerp(u, dot(p[AA + 1], x, y, z - 1),
                    dot(p[BA + 1], x - 1, y, z - 1)),
                lerp(u, dot(p[AB + 1], x, y - 1, z - 1),
                    dot(p[BB + 1], x - 1, y - 1, z - 1)))
        );
    }

    // Octave noise for more natural-looking results
    double octaveNoise(double x, double y, double z, int octaves, double persistence = 0.5) {
        double total = 0;
        double frequency = 1;
        double amplitude = 1;
        double maxValue = 0;

        for (int i = 0; i < octaves; i++) {
            total += noise(x * frequency, y * frequency, z * frequency) * amplitude;

            maxValue += amplitude;
            amplitude *= persistence;
            frequency *= 2;
        }

        return total / maxValue;
    }
};

#endif // PERLIN_NOISE_H