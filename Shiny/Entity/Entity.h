//
// Created by haoxin on 17/2/3.
//

#ifndef SHINY_ENTITY_H
#define SHINY_ENTITY_H

#include "shiny.h"
#include "Model/RawModel.h"
#include "Model/PBRMaterial.h"
#include "glm/glm.hpp"

SHINY_NAMESPACE_BEGIN

class Entity {
public:
	Entity(RawModel *rawModel, PBRMaterial *material, const glm::vec3 &position, const glm::vec3 &rotation, float scaling);
	RawModel *rawModel_;
	PBRMaterial *material_;
    glm::vec3 position_;
    glm::vec3 rotation_;
    float scaling_;
};

SHINY_NAMESPACE_END

#endif //SHINY_ENTITY_H
