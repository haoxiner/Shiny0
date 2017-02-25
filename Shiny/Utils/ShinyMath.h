//
// Created by haoxin on 17/2/12.
//

#ifndef SHINY_SHINYMATH_H
#define SHINY_SHINYMATH_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>
#include "shiny.h"

SHINY_NAMESPACE_BEGIN
/*
 * PI
 */
constexpr float PI = glm::pi<float>();
constexpr float TWO_PI = 2.0f * PI;
constexpr float INV_PI = 1.0f / PI;
constexpr float INV_TWO_PI = 1.0f / TWO_PI;

/*
 * Wrap an angle to [-pi, pi]
 */
inline float wrapAngle(float angle)
{
//    const float invTwoPi = 1.0f / twoPi;
//    return angle - twoPi * std::floorf(angle * invTwoPi);
    while (angle > PI) {
        angle -= TWO_PI;
    }
    while (angle < -PI) {
        angle += TWO_PI;
    }
    return angle;
}



SHINY_NAMESPACE_END

#endif //SHINY_SHINYMATH_H
