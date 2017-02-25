//
// Created by haoxin on 17/2/2.
//

#ifndef SHINY_LOADER_H
#define SHINY_LOADER_H

#include "shiny.h"
#include "Model/RawModel.h"
#include "opengl.h"
#include <vector>
#include <string>

SHINY_NAMESPACE_BEGIN

class Loader {
public:
    RawModel *LoadToVAO(std::vector<float> &positions, std::vector<float> &texCoords, std::vector<int> &indices);
    RawModel *LoadToVAO(std::vector<float> &positions, std::vector<float> &normals, std::vector<float> &texCoords, std::vector<int> &indices);
    RawModel *LoadToVAO(const RawModel &rawModel, std::vector<float> &positions, std::vector<float> &normals, std::vector<float> &texCoords, std::vector<int> &indices);
    GLuint LoadTexture(const std::string &name);
    void Shutdown();
private:
    GLuint CreateVAO();
    void UnbindVAO();
    void StoreDataInAttributeList(int attributeLocation, int elementCountPerVertex, std::vector<float> &data);
    void BindIndicesBuffer(std::vector<int> &indices);
private:
    std::vector<GLuint> vaoList_;
    std::vector<GLuint> vboList_;
    std::vector<GLuint> textureList_;
};

SHINY_NAMESPACE_END

#endif //SHINY_LOADER_H
