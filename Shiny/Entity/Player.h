//
// Created by haoxin on 17/2/7.
//

#ifndef SHINY_PLAYER_H
#define SHINY_PLAYER_H

#include "Shiny.h"
#include "Entity.h"
#include "RenderEngine/input.h"

SHINY_NAMESPACE_BEGIN

class Player : public Entity{
public:
	Player(RawModel *rawModel, PBRMaterial *material, const glm::vec3 &position, const glm::vec3 &rotation, float scaling);
    void Update(float deltaTime, const Input *input);
    float GetRotationToForword() const;
private:
    const float RUN_SPEED = 400;
    const float TURN_SPEED = 3.14 * 0.5;
    float currentRunSpeed_ = 0.0f;
    float currentTurnSpeed_ = 0.0f;
    float rotationToForword_ = 0.0f;
};

SHINY_NAMESPACE_END

#endif //SHINY_PLAYER_H
