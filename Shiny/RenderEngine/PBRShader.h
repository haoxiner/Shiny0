#pragma once

#include "ShaderProgram.h"
#include "Entity/Camera.h"
#include "Entity/Light.h"
#include "glm/glm.hpp"
#include "Shiny.h"

SHINY_NAMESPACE_BEGIN

class PBRShader : public ShaderProgram
{
public:
	bool Startup();
	virtual void BindAttributes();
	virtual void GetAllUniformLocations();
	void LoadModelMatrix(const glm::mat4 &value);
	void LoadViewMatrix(const Camera &camera);
	void LoadProjectionMatrix(const glm::mat4 &value);
	void LoadLight(const Light &light);
private:
	GLint modelMatrixLocation_;
	GLint viewMatrixLocation_;
	GLint projectionMatrixLocation_;
	GLint lightPositionLocation_;
	GLint lightColorLocation_;
};

SHINY_NAMESPACE_END