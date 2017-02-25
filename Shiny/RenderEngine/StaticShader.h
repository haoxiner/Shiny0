//
// Created by haoxin on 17/2/2.
//

#ifndef SHINY_STATICSHADER_H
#define SHINY_STATICSHADER_H

#include "shiny.h"
#include "shaderprogram.h"
#include "Entity/camera.h"
#include "Entity/light.h"
#include "glm/glm.hpp"

SHINY_NAMESPACE_BEGIN

class StaticShader : public ShaderProgram {
public:
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

#endif //SHINY_STATICSHADER_H
