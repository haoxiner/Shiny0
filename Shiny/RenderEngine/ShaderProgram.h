//
// Created by haoxin on 17/2/2.
//

#ifndef SHINY_SHADERPROGRAM_H
#define SHINY_SHADERPROGRAM_H

#include "shiny.h"
#include "opengl.h"
#include "glm/glm.hpp"
#include <string>

SHINY_NAMESPACE_BEGIN

class ShaderProgram {
public:
    void Begin();
    void End();
    void Shutdown();
protected:
    bool Startup(const std::string &vertexShaderSource, const std::string &fragmentShaderSource);
	bool Startup(const std::string &computeShaderSource);
	virtual void BindAttributes() {};
	virtual void GetAllUniformLocations() {};
    void BindAttributeLocation(GLuint attributeLocation, const std::string &name);
    GLint GetUniformLocation(const std::string &name);
	void LoadInteger(GLint location, int value);
    void LoadFloat(GLint location, float value);
    void LoadVector(GLint location, const glm::vec3 &value);
    void LoadMatrix(GLint location, const glm::mat4 &value);
private:
    GLuint LoadShader(const std::string &source, GLenum type);
private:
    GLuint program_;
};

SHINY_NAMESPACE_END

#endif //SHINY_SHADERPROGRAM_H
