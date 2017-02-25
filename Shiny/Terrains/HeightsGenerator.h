//
// Created by haoxin on 17/2/8.
//

#ifndef SHINY_HEIGHTSGENERATOR_H
#define SHINY_HEIGHTSGENERATOR_H

#include "shiny.h"
#include <random>
#include <vector>

SHINY_NAMESPACE_BEGIN

class HeightsGenerator {
public:
    HeightsGenerator();
    ~HeightsGenerator() = default;
    bool Startup(int total);
    float GetHeight(int position);
    float GenerateHeight(int x, int z);
private:
    float GetNoise(int x, int z);
private:
    const float AMPLITUDE = 70.0f;
    int seed_;
    std::default_random_engine randomEngine_;
    std::uniform_real_distribution<float> realDistribution_;
    std::vector<float> randomNumbers;
};

SHINY_NAMESPACE_END

#endif //SHINY_HEIGHTSGENERATOR_H
