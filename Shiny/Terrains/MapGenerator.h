//
// Created by haoxin on 17/2/9.
//

#ifndef SHINY_MAPGENERATOR_H
#define SHINY_MAPGENERATOR_H

#include "shiny.h"

SHINY_NAMESPACE_BEGIN

class MapGenerator {
public:
    MapGenerator();
public:
    int mapWidth_;
    int mapHeight_;
    float noiseScale_;
};

SHINY_NAMESPACE_END

#endif //SHINY_MAPGENERATOR_H
