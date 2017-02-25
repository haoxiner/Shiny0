//
// Created by haoxin on 17/2/5.
//

#ifndef SHINY_TERRAINSHADER_H
#define SHINY_TERRAINSHADER_H

#include "shiny.h"
#include "shaderprogram.h"
#include "Entities/camera.h"
#include "Entities/light.h"
#include "opengl.h"
#include <glm/glm.hpp>

SHINY_NAMESPACE_BEGIN

class TerrainShader : public ShaderProgram {
public:
    TerrainShader() = default;
    ~TerrainShader() = default;
    bool Startup();
    virtual void BindAttributes();
    virtual void GetAllUniformLocations();
    void LoadModelMatrix(const glm::mat4 &value);
    void LoadViewMatrix(const Camera &camera);
    void LoadProjectionMatrix(const glm::mat4 &value);
    void LoadLight(const Light &light);
private:
    GLint modelMatrixLocation_;
    GLint viewMatrixLocation_;
    GLint projectionMatrixLocation_;
    GLint lightPositionLocation_;
    GLint lightColorLocation_;
};

SHINY_NAMESPACE_END

#endif //SHINY_TERRAINSHADER_H
