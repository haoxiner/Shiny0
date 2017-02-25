//
// Created by haoxin on 17/2/2.
//

#include "loader.h"
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

shiny::RawModel * shiny::Loader::LoadToVAO(std::vector<float> &positions, std::vector<float> &texCoords, std::vector<int> &indices) {
    GLuint vao = CreateVAO();
    StoreDataInAttributeList(0, 3, positions);
    StoreDataInAttributeList(1, 2, texCoords);
    BindIndicesBuffer(indices);
    UnbindVAO();
    return new RawModel(vao, indices.size());
}

shiny::RawModel * shiny::Loader::LoadToVAO(std::vector<float> &positions, std::vector<float> &normals,
                                           std::vector<float> &texCoords, std::vector<int> &indices) {
    GLuint vao = CreateVAO();
    StoreDataInAttributeList(0, 3, positions);
    StoreDataInAttributeList(1, 3, normals);
    StoreDataInAttributeList(2, 2, texCoords);
    BindIndicesBuffer(indices);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    UnbindVAO();
    return new RawModel(vao, indices.size());
}

shiny::RawModel * shiny::Loader::LoadToVAO(const RawModel &rawModel, std::vector<float> &positions,
                                           std::vector<float> &normals, std::vector<float> &texCoords,
                                           std::vector<int> &indices) {
    glBindVertexArray(rawModel.GetVAO());
    StoreDataInAttributeList(0, 3, positions);
    StoreDataInAttributeList(1, 3, normals);
    StoreDataInAttributeList(2, 2, texCoords);
    BindIndicesBuffer(indices);
    UnbindVAO();
    return new RawModel(rawModel.GetVAO(), indices.size());
}

GLuint shiny::Loader::LoadTexture(const std::string &name) {
    std::ifstream file(name, std::ios::binary);
    char fileCode[4];
    file.read(fileCode, 4);
    char header[124];
    file.read(header, 124);
    unsigned int height = *(unsigned int*)&(header[8]);
    unsigned int width = *(unsigned int*)&(header[12]);
    unsigned int linearSize = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC = *(unsigned int*)&(header[80]);
    /* how big is it going to be including all mipmaps? */
    unsigned int bufferSize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
    unsigned int format;
    switch (fourCC)
    {
        case FOURCC_DXT1:
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        case FOURCC_DXT3:
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case FOURCC_DXT5:
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            break;
        default:
            return 0;
    }
    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    if (bufferSize == 0) {
        bufferSize = width * height * blockSize;
        mipMapCount = 1;
    }
    std::vector<char> buffer(bufferSize);
    file.read(&buffer[0], bufferSize);
    /* close the file pointer */
    file.close();

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    textureList_.push_back(textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /* load the mipmaps */
    for (unsigned int level = 0, offset = 0; level < mipMapCount && (width || height); ++level)
    {
        unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, &buffer[offset]);
        offset += size;
        width = std::max(1u, width / 2u);
        height = std::max(1u, height / 2u);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipMapCount - 1);
    glBindTexture(GL_TEXTURE_2D, 0);
    return textureID;
}

void shiny::Loader::Shutdown() {
    glDeleteVertexArrays(static_cast<int>(vaoList_.size()), &vaoList_[0]);
    glDeleteBuffers(static_cast<int>(vboList_.size()), &vboList_[0]);
    glDeleteTextures(static_cast<int>(textureList_.size()), &textureList_[0]);
    vaoList_.clear();
    vboList_.clear();
}

GLuint shiny::Loader::CreateVAO() {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    vaoList_.push_back(vao);
    return vao;
}

void shiny::Loader::UnbindVAO() {
    glBindVertexArray(0);
}

void shiny::Loader::StoreDataInAttributeList(int attributeLocation, int elementCountPerVertex, std::vector<float> &data) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(attributeLocation, elementCountPerVertex, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    vboList_.push_back(vbo);
}

void shiny::Loader::BindIndicesBuffer(std::vector<int> &indices) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
    vboList_.push_back(vbo);
}