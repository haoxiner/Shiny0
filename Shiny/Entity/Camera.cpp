//
// Created by haoxin on 17/2/3.
//

#include "camera.h"
#include "Utils/ShinyMath.h"
#include <cmath>

bool shiny::Camera::Startup(float x, float y, float z, float pitch, float yaw, float roll) {
    position_ = glm::vec3(x, y, z);
    pitch_ = pitch;
    yaw_ = yaw;
    roll_ = roll;
    return true;
}

void shiny::Camera::Update(float deltaTime, const Input *input, Player *player) {
    float pitchChange = input->GetRightVerticalAxis() * 0.5f * PI * deltaTime;
    pitch_ += pitchChange;



    float hDis = distanceFromPlayer_ * std::cosf(pitch_);
    float vDis = -distanceFromPlayer_ * std::sinf(pitch_);

//    if (pitch_ > 0) {
//        constexpr float invHalfPi = 1.0f / (PI * 0.5);
//        distanceFromPlayer_ = (1.0f - pitch_ * invHalfPi) * MAX_DISTANCE_FROM_PLAYER;
//        hDis = distanceFromPlayer_ * std::cosf(pitch_);
//        vDis = -distanceFromPlayer_ * std::sinf(pitch_);
//    } else {
//        distanceFromPlayer_ = MAX_DISTANCE_FROM_PLAYER;
//    }


    float theta = glm::radians(-90.0f) - player->GetRotationToForword();
    float offsetX = hDis * std::cosf(theta);
    float offsetZ = hDis * std::sinf(theta);
    position_.x = player->position_.x - offsetX;
    position_.z = player->position_.z - offsetZ;
    position_.y = player->position_.y + vDis + 10;

//    yaw_ = glm::pi<float>() - (theta);
    yaw_ = player->GetRotationToForword();
}

const glm::vec3 &shiny::Camera::GetPosition() const {
    return position_;
}

glm::mat4 shiny::Camera::GetViewMatrix() const {

    auto viewMatrix = glm::rotate(-pitch_, glm::vec3(1,0,0));
    viewMatrix = glm::rotate(viewMatrix, -yaw_, glm::vec3(0,1,0));
    viewMatrix = glm::rotate(viewMatrix, -roll_, glm::vec3(0,0,1));
    viewMatrix = glm::translate(viewMatrix, -position_);

    return viewMatrix;
}