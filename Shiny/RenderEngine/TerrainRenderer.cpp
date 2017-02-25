//
// Created by haoxin on 17/2/5.
//

#include "terrainrenderer.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

bool shiny::TerrainRenderer::Startup(TerrainShader *terrainShader) {
    terrainShader_ = terrainShader;
    return true;
}

void shiny::TerrainRenderer::Render(std::vector<const Terrain *> &terrains) {
    for (auto terrain : terrains) {
        PrepareTerrain(terrain);
        glDrawElements(GL_TRIANGLES, terrain->rawModel_->GetIndicesCount(), GL_UNSIGNED_INT, (void*)0);
    }
    UnbindTerrain();
}

void shiny::TerrainRenderer::PrepareTerrain(const Terrain *terrain) {
    glm::mat4 transformation = glm::translate(glm::vec3(terrain->x_, 0.0f, terrain->z_));
    terrainShader_->LoadModelMatrix(transformation);
    auto rawModel = terrain->rawModel_;
    auto texture = terrain->texture_->GetID();
    glBindVertexArray(rawModel->GetVAO());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void shiny::TerrainRenderer::UnbindTerrain() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}