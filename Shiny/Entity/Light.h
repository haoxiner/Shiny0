//
// Created by haoxin on 17/2/5.
//

#ifndef SHINY_LIGHT_H
#define SHINY_LIGHT_H

#include "shiny.h"
#include <glm/glm.hpp>

SHINY_NAMESPACE_BEGIN

class Light {
public:
    Light();
    const glm::vec3 &GetPosition() const;
    const glm::vec3 &GetColor() const;
private:
    glm::vec3 position_;
    glm::vec3 color_;
};

SHINY_NAMESPACE_END

#endif //SHINY_LIGHT_H
