//
// Created by haoxin on 17/2/5.
//

#include "light.h"

shiny::Light::Light() {
    color_.x = color_.y = color_.z = 1.0f;
}

const glm::vec3& shiny::Light::GetPosition() const {
    return position_;
}

const glm::vec3& shiny::Light::GetColor() const {
    return color_;
}