//
// Created by haoxin on 17/2/2.
//

#include "staticshader.h"
#include "glm/gtx/transform.hpp"
#include <fstream>

bool shiny::StaticShader::Startup() {
    std::ifstream file;
    file.open("Shader/depth.vert.glsl");
    std::istreambuf_iterator<char> vsBegin(file), vsEnd;
    std::string vertexShaderSource(vsBegin, vsEnd);
    file.close();
    file.clear();

    file.open("Shader/depth.frag.glsl");
    std::istreambuf_iterator<char> fsBegin(file), fsEnd;
    std::string fragmentShaderSource(fsBegin, fsEnd);
    file.close();
    file.clear();
    bool success = ShaderProgram::Startup(vertexShaderSource, fragmentShaderSource);
    if (!success) {
        return false;
    }
	//Begin();
	//LoadInteger(GetUniformLocation("albedoMap"), 0);
	//LoadInteger(GetUniformLocation("metallicMap"), 1);
	//LoadInteger(GetUniformLocation("roughnessMap"), 2);
	//LoadInteger(GetUniformLocation("normalMap"), 3);
	//End();
    return true;
}

void shiny::StaticShader::BindAttributes() {
    BindAttributeLocation(0, "position");
    //BindAttributeLocation(1, "normal");
    //BindAttributeLocation(2, "texCoord");
}

void shiny::StaticShader::GetAllUniformLocations() {
    modelMatrixLocation_ = GetUniformLocation("modelMatrix");
    viewMatrixLocation_ = GetUniformLocation("viewMatrix");
    projectionMatrixLocation_ = GetUniformLocation("projectionMatrix");
    //lightPositionLocation_ = GetUniformLocation("lightPosition");
    //lightColorLocation_ = GetUniformLocation("lightColor");
}

void shiny::StaticShader::LoadModelMatrix(const glm::mat4 &value) {
    LoadMatrix(modelMatrixLocation_, value);
}

void shiny::StaticShader::LoadViewMatrix(const Camera &camera) {
    LoadMatrix(viewMatrixLocation_, camera.GetViewMatrix());
}

void shiny::StaticShader::LoadProjectionMatrix(const glm::mat4 &value) {
    LoadMatrix(projectionMatrixLocation_, value);
}

void shiny::StaticShader::LoadLight(const Light &light) {
    LoadVector(lightPositionLocation_, light.GetPosition());
    LoadVector(lightColorLocation_, light.GetColor());
}