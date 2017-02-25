//
// Created by haoxin on 17/2/5.
//

#ifndef SHINY_ENTITYRENDERER_H
#define SHINY_ENTITYRENDERER_H

#include "shiny.h"
#include "staticshader.h"
#include "Entity/entity.h"
#include "Model/PBRMaterial.h"
#include <vector>
#include <map>

SHINY_NAMESPACE_BEGIN

class EntityRenderer {
public:
    EntityRenderer() = default;
    ~EntityRenderer() = default;
    bool Startup(StaticShader *staticShader);
    void Render(std::vector<const Entity*> &entities);
private:
	// transformation
    void PrepareInstance(const Entity &entity);
private:
    StaticShader *staticShader_ = nullptr;
};

SHINY_NAMESPACE_END

#endif //SHINY_ENTITYRENDERER_H
