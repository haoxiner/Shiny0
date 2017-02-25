//
// Created by haoxin on 17/2/9.
//

#include "noise.h"
#include "Utils/perlinnoise.h"
#include <limits>
#include <random>
#include <vector>
#include <utility>

void shiny::Noise::GenerateNoiseMap(float *noiseMap, int width, int height, float scale, int octaves, float persistance,
                                    float lacunarity, float offsetX, float offsetY, unsigned int seed) {
    if (scale <= 0) {
        scale = 0.0001f;
    }

    std::default_random_engine octaveRandomEngine(seed);
    std::uniform_int_distribution<int> octaveOffsetDistribution(-100000, 100000);
    std::vector<std::pair<float, float>> octaveOffsets;
    for (int i = 0; i < octaves; i++) {
        float x = octaveOffsetDistribution(octaveRandomEngine) + offsetX;
        float y = octaveOffsetDistribution(octaveRandomEngine) + offsetY;
        octaveOffsets.emplace_back(x, y);
    }

    PerlinNoise perlinNoise(seed);
    float maxNoiseHeight = std::numeric_limits<float>::min();
    float minNoiseHeight = std::numeric_limits<float>::max();
    const float halfWidth = width / 2.0f;
    const float halfHeight = height / 2.0f;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float amplitude = 1;
            float frequency = 1;
            float noiseHeight = 0;
            for (int i = 0; i < octaves; i++) {
                float sampleX = (x - halfWidth + octaveOffsets[i].first) / scale * frequency;
                float sampleY = (y - halfHeight + octaveOffsets[i].second) / scale * frequency;
                float perlinValue = perlinNoise.Noise(sampleX, sampleY, 0.0f);
                noiseHeight += perlinValue * amplitude;
                amplitude *= persistance;
                frequency *= lacunarity;
            }
            if (noiseHeight > maxNoiseHeight) {
                maxNoiseHeight = noiseHeight;
            } else if (noiseHeight < minNoiseHeight) {
                minNoiseHeight = noiseHeight;
            }
            noiseMap[y * width + x] = noiseHeight;
        }
    }
    float heightDifference = maxNoiseHeight - minNoiseHeight;
    if (heightDifference != 0) {
        // normalize to [-1,1]
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                noiseMap[y * width + x] = (noiseMap[y * width + x] - minNoiseHeight) / heightDifference;
            }
        }
    }
}