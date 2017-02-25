//
// Created by haoxin on 17/2/3.
//

#include "entity.h"

shiny::Entity::Entity(RawModel *rawModel, PBRMaterial *material, const glm::vec3 &position, const glm::vec3 &rotation, float scaling)
	:rawModel_(rawModel), material_(material), position_(position), rotation_(rotation), scaling_(scaling)
{
}
