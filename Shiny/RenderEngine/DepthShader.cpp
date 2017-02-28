#include "DepthShader.h"
#include <fstream>

bool shiny::DepthShader::Startup()
{
	std::ifstream file;
	file.open("Shader/depth.vert.glsl");
	std::istreambuf_iterator<char> vsBegin(file), vsEnd;
	std::string vertexShaderSource(vsBegin, vsEnd);
	file.close();
	file.clear();

	file.open("Shader/depth.frag.glsl");
	std::istreambuf_iterator<char> fsBegin(file), fsEnd;
	std::string fragmentShaderSource(fsBegin, fsEnd);
	file.close();
	file.clear();
	bool success = ShaderProgram::Startup(vertexShaderSource, fragmentShaderSource);
	if (!success) {
		return false;
	}
	return true;
}

void shiny::DepthShader::BindAttributes() {
	BindAttributeLocation(0, "position");
}

void shiny::DepthShader::GetAllUniformLocations() {
	modelMatrixLocation_ = GetUniformLocation("modelMatrix");
	viewMatrixLocation_ = GetUniformLocation("viewMatrix");
	projectionMatrixLocation_ = GetUniformLocation("projectionMatrix");
}

void shiny::DepthShader::LoadModelMatrix(const glm::mat4 &value) {
	LoadMatrix(modelMatrixLocation_, value);
}

void shiny::DepthShader::LoadViewMatrix(const Camera &camera) {
	LoadMatrix(viewMatrixLocation_, camera.GetViewMatrix());
}

void shiny::DepthShader::LoadProjectionMatrix(const glm::mat4 &value) {
	LoadMatrix(projectionMatrixLocation_, value);
}