//
// Created by haoxin on 17/2/5.
//

#ifndef SHINY_TERRAINRENDERER_H
#define SHINY_TERRAINRENDERER_H

#include "shiny.h"
#include "terrainshader.h"
#include "Terrains/terrain.h"
#include <vector>

SHINY_NAMESPACE_BEGIN

class TerrainRenderer {
public:
    TerrainRenderer() = default;
    ~TerrainRenderer() = default;
    bool Startup(TerrainShader *terrainShader);
    void Render(std::vector<const Terrain*> &terrains);
    void PrepareTerrain(const Terrain *terrain);
    void UnbindTerrain();
private:
    TerrainShader *terrainShader_ = nullptr;
};

SHINY_NAMESPACE_END

#endif //SHINY_TERRAINRENDERER_H
