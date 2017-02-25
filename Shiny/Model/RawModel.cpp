//
// Created by haoxin on 17/2/1.
//

#include "RawModel.h"

shiny::RawModel::RawModel(GLuint vao, GLsizei indicesCount): vao_(vao), indicesCount_(indicesCount)
{

}

GLuint shiny::RawModel::GetVAO() const
{
    return vao_;
}

GLsizei shiny::RawModel::GetIndicesCount() const
{
    return indicesCount_;
}