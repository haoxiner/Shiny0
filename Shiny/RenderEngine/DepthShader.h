#pragma once

#include "ShaderProgram.h"
#include "Entity/Camera.h"
#include "Entity/Light.h"
#include "glm/glm.hpp"
#include "Shiny.h"

SHINY_NAMESPACE_BEGIN

class DepthShader : public ShaderProgram
{
public:
	bool Startup();
	virtual void BindAttributes();
	virtual void GetAllUniformLocations();
	void LoadModelMatrix(const glm::mat4 &value);
	void LoadViewMatrix(const Camera &camera);
	void LoadProjectionMatrix(const glm::mat4 &value);
private:
	GLint modelMatrixLocation_;
	GLint viewMatrixLocation_;
	GLint projectionMatrixLocation_;
};

SHINY_NAMESPACE_END