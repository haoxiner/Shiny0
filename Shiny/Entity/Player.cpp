//
// Created by haoxin on 17/2/7.
//

#include "player.h"
#include "Utils/ShinyMath.h"
#include <cmath>

shiny::Player::Player(RawModel *rawModel, PBRMaterial *material, const glm::vec3 &position, const glm::vec3 &rotation, float scaling)
	:Entity(rawModel, material, position, rotation, scaling), rotationToForword_(rotation.y)
{
}

void shiny::Player::Update(float deltaTime, const Input *input) {
    // look direction
    float turnForwardDirection = input->GetRightHorizontalAxis();
    if (turnForwardDirection > 0) {
        currentTurnSpeed_ = -TURN_SPEED;
    } else if (turnForwardDirection < 0) {
        currentTurnSpeed_ = TURN_SPEED;
    } else {
        currentTurnSpeed_ = 0;
    }
    rotationToForword_ += currentTurnSpeed_ * deltaTime;
    rotationToForword_ = wrapAngle(rotationToForword_);

    // body rotation
    float vertical = input->GetLeftVerticalAxis();
    float horizontal = input->GetLeftHorizontalAxis();
    currentRunSpeed_ = RUN_SPEED;
    float bodyRotation = rotation_.y - rotationToForword_;
    if (horizontal > 0){
        if (vertical > 0) {
            bodyRotation = glm::radians(-45.0f);
        } else if (vertical < 0) {
            bodyRotation = glm::radians(-125.0f);
        } else {
            bodyRotation = glm::radians(-90.0f);
        }
    } else if (horizontal < 0) {
        if (vertical > 0) {
            bodyRotation = glm::radians(45.0f);
        } else if (vertical < 0) {
            bodyRotation = glm::radians(125.0f);
        } else {
            bodyRotation = glm::radians(90.0f);
        }
    } else {
        if (vertical > 0) {
            bodyRotation = 0.0f;
        } else if (vertical < 0) {
            bodyRotation = glm::radians(180.0f);
        } else {
            currentRunSpeed_ = 0.0f;
        }
    }
    bodyRotation = wrapAngle(bodyRotation + rotationToForword_);
    float deltaRotation = wrapAngle(bodyRotation - rotation_.y);
    float totalTime = std::fabsf(deltaRotation * 1.0f / (4.0f * TWO_PI));
    if (totalTime <= deltaTime) {
        rotation_.y = bodyRotation;
        float distance = currentRunSpeed_ * deltaTime;
        if (input->Fire0()) {
            position_.y += distance * vertical;
        } else {
            float dx = distance * std::sinf(rotation_.y);
            float dz = distance * std::cosf(rotation_.y);
            position_.x -= dx;
            position_.z -= dz;
        }
    } else {
        float rotationPercent = deltaTime / totalTime;
        rotation_.y = wrapAngle(rotation_.y + deltaRotation * rotationPercent);
    }
}

float shiny::Player::GetRotationToForword() const {
    return rotationToForword_;
}