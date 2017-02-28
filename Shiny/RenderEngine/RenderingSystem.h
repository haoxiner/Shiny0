//
// Created by haoxin on 17/2/3.
//

#ifndef SHINY_RENDERINGSYSTEM_H
#define SHINY_RENDERINGSYSTEM_H

#include "Shiny.h"
#include "Staticshader.h"
#include "DepthShader.h"
#include "ScreenShader.h"
#include "EntityRenderer.h"
#include "Entity/entity.h"
#include "opengl.h"
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
    static const float NEAR_PLANE;
	static const float FAR_PLANE;
    StaticShader staticShader_;
    EntityRenderer entityRenderer_;
	DepthShader depthShader_;
	ScreenShader screenShader_;
    std::vector<const Entity*> entities_;

	GLuint depthMapFrameBuffer_;
	GLuint depthMap_;

	GLuint quadVAO_;
	GLuint quadPositionVBO_;
	GLuint quadTexCoordVBO_;
};

SHINY_NAMESPACE_END

#endif //SHINY_MASTERRENDERER_H
