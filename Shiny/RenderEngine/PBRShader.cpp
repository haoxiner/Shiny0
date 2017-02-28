#include "PBRShader.h"

bool shiny::PBRShader::Startup()
{
	return true;
}

void shiny::PBRShader::BindAttributes()
{
}

void shiny::PBRShader::GetAllUniformLocations()
{
}

void shiny::PBRShader::LoadModelMatrix(const glm::mat4 &value)
{
}

void shiny::PBRShader::LoadViewMatrix(const Camera &camera)
{
}

void shiny::PBRShader::LoadProjectionMatrix(const glm::mat4 &value)
{
}

void shiny::PBRShader::LoadLight(const Light &light)
{
}
