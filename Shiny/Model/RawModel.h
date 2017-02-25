//
// Created by haoxin on 17/2/1.
//

#ifndef SHINY_RAWMODEL_H
#define SHINY_RAWMODEL_H

#include "shiny.h"
#include "opengl.h"

SHINY_NAMESPACE_BEGIN

class RawModel
{
public:
    RawModel(GLuint vao, GLsizei indicesCount);
    GLuint GetVAO() const;
    GLsizei GetIndicesCount() const;
private:
    GLuint vao_;
    GLsizei indicesCount_;
};

SHINY_NAMESPACE_END

#endif //SHINY_RAWMODEL_H
