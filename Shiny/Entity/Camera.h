//
// Created by haoxin on 17/2/3.
//

#ifndef SHINY_CAMERA_H
#define SHINY_CAMERA_H

#include "shiny.h"
#include "RenderEngine/input.h"
#include "Entity/player.h"
#include <glm/glm.hpp>

SHINY_NAMESPACE_BEGIN

class Camera {
public:
    bool Startup(float x, float y, float z, float pitch, float yaw, float roll);
    void Update(float deltaTime, const Input *input, Player *player);
    const glm::vec3 &GetPosition() const;
    glm::mat4 GetViewMatrix() const;
private:
private:
    const float MAX_DISTANCE_FROM_PLAYER = 100.0f;
    float distanceFromPlayer_ = 100.0f;
    float angleAroundPlayer_ = 0.0f;
    glm::vec3 position_;
    float pitch_ = 0.0f;
    float yaw_ = 0.0f;
    float roll_ = 0.0f;
};

SHINY_NAMESPACE_END

#endif //SHINY_CAMERA_H
