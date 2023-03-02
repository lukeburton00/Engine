#include "PerlinNoise.hpp"
#include "Random.hpp"

#include <cmath>
#include <algorithm>
#include <random>
#include <vector>

PerlinNoise::PerlinNoise(int seed) 
{
    p.resize(256);
    std::iota(p.begin(), p.end(), 0);
    std::default_random_engine engine(seed);
    std::shuffle(p.begin(), p.end(), engine);
    p.insert(p.end(), p.begin(), p.end());
}

float PerlinNoise::noise(float x, float y, float z, float frequency, float amplitude, int octaves, float lacunarity, float persistence) const 
{
    float maxAmplitude = 0.0f;
    float result = 0.0f;
    float scale = 1.0f;

    float center_x = 200.0f / 2.0f;
    float center_y = 150.0f / 2.0f;
    float radius = std::min(center_x, center_y);
    printf("%f, %f\n", center_x, center_y);

    for (int i = 0; i < octaves; ++i) {
        result += noiseImpl(x * frequency, y * frequency, 0.0f) * scale;
        maxAmplitude += scale;
        scale *= amplitude;
        frequency *= 2.0f;
        amplitude *= persistence;
    }

    float dist_x = std::abs(x - center_x);
    float dist_y = std::abs(y - center_y);
    float dist = std::sqrt(dist_x * dist_x + dist_y * dist_y);

    printf("%f\n", dist);

    return result / maxAmplitude;
}

float PerlinNoise::noiseImpl(float x, float y, float z) const
{

    int X = static_cast<int>(std::floor(x)) & 255;
    int Y = static_cast<int>(std::floor(y)) & 255;
    int Z = static_cast<int>(std::floor(z)) & 255;

    x -= std::floor(x);
    y -= std::floor(y);
    z -= std::floor(z);

    float u = fade(x);
    float v = fade(y);
    float w = fade(z);

    int A = p[X] + Y;
    int AA = p[A] + Z;
    int AB = p[A + 1] + Z;
    int B = p[X + 1] + Y;
    int BA = p[B] + Z;
    int BB = p[B + 1] + Z;

    float res = lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z),
                                        grad(p[BA], x - 1, y, z)),
                                lerp(u, grad(p[AB], x, y - 1, z),
                                    grad(p[BB], x - 1, y - 1, z))),
                        lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1),
                                    grad(p[BA + 1], x - 1, y, z - 1)),
                            lerp(u, grad(p[AB + 1], x, y - 1, z - 1),
                                grad(p[BB + 1], x - 1, y - 1, z - 1))));
    return (res + 1.0) / 2.0;
}


float PerlinNoise::fade(float t) 
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float PerlinNoise::lerp(float t, float a, float b) 
{
    return a + t * (b - a);
}

float PerlinNoise::grad(int hash, float x, float y, float z) 
{
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : (h == 12 || h == 14 ? x : z);
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}