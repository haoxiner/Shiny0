//
// Created by haoxin on 17/2/9.
//

#include "perlinnoise.h"
#include <numeric>
#include <random>
#include <cmath>
#include <algorithm>

shiny::PerlinNoise::PerlinNoise() {
    permutation_ = {
            151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
            8,99,37,240,21,10,23,190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
            35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,
            134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
            55,46,245,40,244,102,143,54, 65,25,63,161,1,216,80,73,209,76,132,187,208, 89,
            18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,
            250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,
            189,28,42,223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167,
            43,172,9,129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,
            97,228,251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,
            107,49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
            138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180 };
    // Duplicate the permutation vector
    permutation_.insert(permutation_.end(), permutation_.begin(), permutation_.end());
}

shiny::PerlinNoise::PerlinNoise(unsigned int seed) {
    permutation_.resize(256);
    std::iota(permutation_.begin(), permutation_.end(), 0);
    std::default_random_engine engine(seed);
    std::shuffle(permutation_.begin(), permutation_.end(), engine);
    permutation_.insert(permutation_.end(), permutation_.begin(), permutation_.end());
}

float shiny::PerlinNoise::Noise(float x, float y, float z) {
    int X = static_cast<int>(std::floorf(x)) & 255;
    int Y = static_cast<int>(std::floorf(y)) & 255;
    int Z = static_cast<int>(std::floorf(z)) & 255;
    x -= std::floorf(x);
    y -= std::floorf(y);
    z -= std::floorf(z);
    float u = Fade(x);
    float v = Fade(y);
    float w = Fade(z);
    int A = permutation_[X]+Y;
    int AA = permutation_[A]+Z;
    int AB = permutation_[A+1]+Z;
    int B = permutation_[X+1]+Y;
    int BA = permutation_[B]+Z;
    int BB = permutation_[B+1]+Z;
    return Lerp(Lerp(Lerp(Grad(x, y, z, permutation_[AA]), Grad(x-1, y, z, permutation_[BA]), u), Lerp(Grad(x, y-1, z, permutation_[AB]), Grad(x-1, y-1, z, permutation_[BB]), u), v), Lerp(Lerp(Grad(x ,y, z - 1, permutation_[AA+1]), Grad(x - 1, y, z - 1, permutation_[BA+1]),u), Lerp(Grad(x, y-1, z-1, permutation_[AB+1]), Grad(x-1, y-1, z-1, permutation_[BB+1]),u), v), w);
}

float shiny::PerlinNoise::Fade(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float shiny::PerlinNoise::Lerp(float a, float b, float t) {
    return a + t * (b - a);
}

float shiny::PerlinNoise::Grad(float x, float y, float z, int hash) {
    int h = hash & 15; // CONVERT LO 4 BITS OF HASH CODE
    // INTO 12 GRADIENT DIRECTIONS.
    double u = h < 8 ? x : y, v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}