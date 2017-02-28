#pragma once

#include "ShaderProgram.h"
#include "Entity/Camera.h"
#include "Entity/Light.h"
#include "glm/glm.hpp"
#include "Shiny.h"

SHINY_NAMESPACE_BEGIN

class LightCullingProgram : public ShaderProgram
{
public:
	bool Startup();
};

SHINY_NAMESPACE_END