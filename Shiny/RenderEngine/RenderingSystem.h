//
// Created by haoxin on 17/2/3.
//

#ifndef SHINY_MASTERRENDERER_H
#define SHINY_MASTERRENDERER_H

#include "shiny.h"
#include "staticshader.h"
#include "EntityRenderer.h"
#include "Entity/entity.h"
#include <vector>

SHINY_NAMESPACE_BEGIN

class RenderingSystem {
public:
    RenderingSystem() = default;
    ~RenderingSystem() = default;
    bool Startup(float xResolution, float yResolution);
    void Process(const Entity *entity);
    void Prepare();
    void Render(const Light &light, const Camera &camera);
private:
    static const float FOV;
    static const float Z_NEAR;
	static const float Z_FAR;
    StaticShader staticShader_;
    EntityRenderer entityRenderer_;
    std::vector<const Entity*> entities_;
};

SHINY_NAMESPACE_END

#endif //SHINY_MASTERRENDERER_H
