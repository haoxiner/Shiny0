#include "PBRMaterial.h"

shiny::PBRMaterial::PBRMaterial(GLuint albedoMap, GLuint metallicMap, GLuint roughnessMap, GLuint normalMap)
	:albedoMap_(albedoMap), metallicMap_(metallicMap), roughnessMap_(roughnessMap), normalMap_(normalMap)
{
}

GLuint shiny::PBRMaterial::GetAlbedoMap() const
{
	return albedoMap_;
}

GLuint shiny::PBRMaterial::GetMetallicMap() const
{
	return metallicMap_;
}

GLuint shiny::PBRMaterial::GetRoughnessMap() const
{
	return roughnessMap_;
}

GLuint shiny::PBRMaterial::GetNormalMap() const
{
	return normalMap_;
}
