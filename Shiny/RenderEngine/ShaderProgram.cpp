//
// Created by haoxin on 17/2/2.
//

#include "shaderprogram.h"
#include <fstream>
#include <iostream>
#include <vector>

bool shiny::ShaderProgram::Startup(const std::string &vertexShaderSource, const std::string &fragmentShaderSource) {
    vertexShader_ = LoaderShader(vertexShaderSource, GL_VERTEX_SHADER);
    fragmentShader_ = LoaderShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    program_ = glCreateProgram();
    glAttachShader(program_, vertexShader_);
    glAttachShader(program_, fragmentShader_);
    BindAttributes();
    glLinkProgram(program_);
    GLint success = GL_FALSE;
    glGetProgramiv(program_, GL_LINK_STATUS, &success);
    if (success != GL_TRUE) {
        GLint logLength;
        glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> infoLog(logLength);
        glGetProgramInfoLog(program_, logLength, &logLength, &infoLog[0]);
        std::cerr << &infoLog[0] << std::endl;
    }
    GetAllUniformLocations();
    return true;
}

void shiny::ShaderProgram::Begin() {
    glUseProgram(program_);
}

void shiny::ShaderProgram::End() {
    glUseProgram(0);
}

void shiny::ShaderProgram::Shutdown() {
    glDeleteProgram(program_);
    glDeleteShader(vertexShader_);
    glDeleteShader(fragmentShader_);
}

void shiny::ShaderProgram::BindAttributeLocation(GLuint attributeLocation, const std::string &name) {
    glBindAttribLocation(program_, attributeLocation, name.c_str());
}

GLint shiny::ShaderProgram::GetUniformLocation(const std::string &name) {
    return glGetUniformLocation(program_, name.c_str());
}

void shiny::ShaderProgram::LoadInteger(GLint location, int value)
{
	glUniform1i(location, value);
}

void shiny::ShaderProgram::LoadFloat(GLint location, float value) {
    glUniform1f(location, value);
}

void shiny::ShaderProgram::LoadVector(GLint location, const glm::vec3 &value) {
    glUniform3fv(location, 1, &value[0]);
}

void shiny::ShaderProgram::LoadMatrix(GLint location, const glm::mat4 &value) {
    glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

GLuint shiny::ShaderProgram::LoaderShader(const std::string &source, GLenum type) {
    GLuint shader = glCreateShader(type);
    const char *const sourcePointer = source.c_str();
    glShaderSource(shader, 1, &sourcePointer, nullptr);
    glCompileShader(shader);
    GLint success = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE) {
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> infoLog(logLength);
        glGetShaderInfoLog(shader, logLength, &logLength, &infoLog[0]);
        std::cerr << &infoLog[0] << std::endl;
    }
    return shader;
}