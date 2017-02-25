#pragma once
#include "Shiny.h"
#include "opengl.h"

SHINY_NAMESPACE_BEGIN

class PBRMaterial
{
public:
	PBRMaterial(GLuint albedoMap, GLuint metallicMap, GLuint roughnessMap, GLuint normalMap);
	~PBRMaterial() = default;
	GLuint GetAlbedoMap() const;
	GLuint GetMetallicMap() const;
	GLuint GetRoughnessMap() const;
	GLuint GetNormalMap() const;
private:
	GLuint albedoMap_ = 0;
	GLuint metallicMap_ = 0;
	GLuint roughnessMap_ = 0;
	GLuint normalMap_ = 0;
};

SHINY_NAMESPACE_END