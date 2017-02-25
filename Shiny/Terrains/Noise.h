//
// Created by haoxin on 17/2/9.
//

#ifndef SHINY_NOISE_H
#define SHINY_NOISE_H

#include "shiny.h"

SHINY_NAMESPACE_BEGIN

class Noise {
public:
    void GenerateNoiseMap(float *noiseMap,
                          int width,
                          int height,
                          float scale,
                          int octaves,
                          float persistance,
                          float lacunarity,
                          float offsetX,
                          float offsetY,
                          unsigned int seed);
};

SHINY_NAMESPACE_END

#endif //SHINY_NOISE_H
