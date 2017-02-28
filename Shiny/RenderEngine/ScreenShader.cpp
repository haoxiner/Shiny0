#include "ScreenShader.h"
#include <fstream>

bool shiny::ScreenShader::Startup()
{
	std::ifstream file;
	file.open("Shader/quad2d.vert.glsl");
	std::istreambuf_iterator<char> vsBegin(file), vsEnd;
	std::string vertexShaderSource(vsBegin, vsEnd);
	file.close();
	file.clear();

	file.open("Shader/screen.frag.glsl");
	std::istreambuf_iterator<char> fsBegin(file), fsEnd;
	std::string fragmentShaderSource(fsBegin, fsEnd);
	file.close();
	file.clear();
	bool success = ShaderProgram::Startup(vertexShaderSource, fragmentShaderSource);
	if (!success) {
		return false;
	}

	Begin();
	LoadInteger(GetUniformLocation("colorMap"), 0);
	End();
	return true;
}

void shiny::ScreenShader::BindAttributes() {
	BindAttributeLocation(0, "position");
	BindAttributeLocation(1, "texCoord");
}

void shiny::ScreenShader::GetAllUniformLocations() {
}