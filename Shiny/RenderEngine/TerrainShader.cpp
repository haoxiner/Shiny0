//
// Created by haoxin on 17/2/5.
//

#include "terrainshader.h"
#include "glm/gtx/transform.hpp"
#include <fstream>

bool shiny::TerrainShader::Startup() {
    std::ifstream file;
    file.open("Shader/terrain.vert.glsl");
    std::istreambuf_iterator<char> vsBegin(file), vsEnd;
    std::string vertexShaderSource(vsBegin, vsEnd);
    file.close();
    file.clear();

    file.open("Shader/terrain.frag.glsl");
    std::istreambuf_iterator<char> fsBegin(file), fsEnd;
    std::string fragmentShaderSource(fsBegin, fsEnd);
    file.close();
    file.clear();
    bool success = ShaderProgram::Startup(vertexShaderSource, fragmentShaderSource);
    if (!success) {
        return false;
    }
    return true;
}

void shiny::TerrainShader::BindAttributes() {
    BindAttributeLocation(0, "position");
    BindAttributeLocation(1, "normal");
    BindAttributeLocation(2, "texCoord");
}

void shiny::TerrainShader::GetAllUniformLocations() {
    modelMatrixLocation_ = GetUniformLocation("modelMatrix");
    viewMatrixLocation_ = GetUniformLocation("viewMatrix");
    projectionMatrixLocation_ = GetUniformLocation("projectionMatrix");
    lightPositionLocation_ = GetUniformLocation("lightPosition");
    lightColorLocation_ = GetUniformLocation("lightColor");
}

void shiny::TerrainShader::LoadModelMatrix(const glm::mat4 &value) {
    LoadMatrix(modelMatrixLocation_, value);
}

void shiny::TerrainShader::LoadViewMatrix(const Camera &camera) {
    LoadMatrix(viewMatrixLocation_, camera.GetViewMatrix());
}

void shiny::TerrainShader::LoadProjectionMatrix(const glm::mat4 &value) {
    LoadMatrix(projectionMatrixLocation_, value);
}

void shiny::TerrainShader::LoadLight(const Light &light) {
    LoadVector(lightPositionLocation_, light.GetPosition());
    LoadVector(lightColorLocation_, light.GetColor());
}