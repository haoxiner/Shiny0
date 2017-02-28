#pragma once

#include "ShaderProgram.h"
#include "Entity/Camera.h"
#include "Entity/Light.h"
#include "glm/glm.hpp"
#include "Shiny.h"

SHINY_NAMESPACE_BEGIN

class ScreenShader : public ShaderProgram
{
public:
	bool Startup();
	virtual void BindAttributes();
	virtual void GetAllUniformLocations();
};

SHINY_NAMESPACE_END