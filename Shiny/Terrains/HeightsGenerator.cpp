//
// Created by haoxin on 17/2/8.
//

#include "heightsgenerator.h"
#include "Utils/perlinnoise.h"

shiny::HeightsGenerator::HeightsGenerator():realDistribution_(0,1) {

}

bool shiny::HeightsGenerator::Startup(int total) {
    for (int i = 0; i < total; ++i) {
        randomNumbers.push_back(realDistribution_(randomEngine_));
    }
    return true;
}

float shiny::HeightsGenerator::GetHeight(int position) {
    return randomNumbers[position] * AMPLITUDE;
}

float shiny::HeightsGenerator::GenerateHeight(int x, int z) {
    return GetNoise(x, z) * AMPLITUDE;
}

float shiny::HeightsGenerator::GetNoise(int x, int z) {
    return realDistribution_(randomEngine_);
}