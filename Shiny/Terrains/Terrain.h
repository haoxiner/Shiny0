//
// Created by haoxin on 17/2/5.
//

#ifndef SHINY_TERRAIN_H
#define SHINY_TERRAIN_H

#include "shiny.h"
#include "Model/RawModel.h"
#include "Texture/modeltexture.h"
#include "RenderEngine/loader.h"

SHINY_NAMESPACE_BEGIN

class Terrain {
public:
    Terrain(float gridX,
            float gridZ,
            ModelTexture *modelTexture,
            Loader &loader,
            float scale,
            int octaves,
            float persistance,
            float lacunarity,
            float offsetX,
            float offsetY,
            int levelOfDetail,
            unsigned int seed);
    void Change(Loader &loader,
                float scale,
                int octaves,
                float persistance,
                float lacunarity,
                float offsetX,
                float offsetY,
                int levelOfDetail,
                unsigned int seed);
public:
    const float SIZE = 800;
    const float VERTEX_COUNT_PER_LINE = 128;
    const float x_;
    const float z_;
    RawModel *rawModel_;
    ModelTexture *texture_;
private:
    RawModel *Generate(Loader &loader, float scale, int octaves, float persistance,
                       float lacunarity, float offsetX, float offsetY, int levelOfDetail, unsigned int seed);
};

SHINY_NAMESPACE_END

#endif //SHINY_TERRAIN_H
