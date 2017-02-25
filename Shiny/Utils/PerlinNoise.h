//
// Created by haoxin on 17/2/9.
//

#ifndef SHINY_PERLINNOISE_H
#define SHINY_PERLINNOISE_H

#include "shiny.h"
#include <vector>

SHINY_NAMESPACE_BEGIN

class PerlinNoise {
public:
    PerlinNoise();
    PerlinNoise(unsigned int seed);
    float Noise(float x, float y, float z);
private:
    float Fade(float t);
    float Lerp(float a, float b, float t);
    float Grad(float x, float y, float z, int hash);
private:
    std::vector<int> permutation_;
};

SHINY_NAMESPACE_END

#endif //SHINY_PERLINNOISE_H
