//
// Created by haoxin on 17/2/3.
//

#include "RenderingSystem.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

const float shiny::RenderingSystem::FOV = glm::radians(70.0f);
const float shiny::RenderingSystem::Z_NEAR = 0.1f;
const float shiny::RenderingSystem::Z_FAR = 10000.0f;

bool shiny::RenderingSystem::Startup(float xResolution, float yResolution) {
    float aspectRatio = xResolution / yResolution;
    auto projectionMatrix = glm::perspective(FOV, aspectRatio, Z_NEAR, Z_FAR);
    staticShader_.Startup();
    staticShader_.Begin();
    staticShader_.LoadProjectionMatrix(projectionMatrix);
    staticShader_.End();
    entityRenderer_.Startup(&staticShader_);
    return true;
}

void shiny::RenderingSystem::Process(const Entity *entity) {
    entities_.push_back(entity);
}

void shiny::RenderingSystem::Prepare() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void shiny::RenderingSystem::Render(const Light &light, const Camera &camera) {
    staticShader_.Begin();
    staticShader_.LoadLight(light);
    staticShader_.LoadViewMatrix(camera);
    entityRenderer_.Render(entities_);
    staticShader_.End();
}