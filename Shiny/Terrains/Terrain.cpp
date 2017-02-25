//
// Created by haoxin on 17/2/5.
//

#include "terrain.h"
#include "noise.h"
#include <vector>

shiny::Terrain::Terrain(float gridX,
                        float gridZ,
                        ModelTexture *modelTexture,
                        Loader &loader,
                        float scale,
                        int octaves,
                        float persistance,
                        float lacunarity,
                        float offsetX,
                        float offsetY,
                        int levelOfDetail,
                        unsigned int seed):
        x_(gridX * SIZE), z_(gridZ * SIZE), texture_(modelTexture), rawModel_(Generate(loader, scale, octaves, persistance, lacunarity, offsetX, offsetY, levelOfDetail, seed)) {

}

void shiny::Terrain::Change(Loader &loader, float scale, int octaves, float persistance, float lacunarity, float offsetX, float offsetY,
                            int levelOfDetail, unsigned int seed) {
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> texCoords;
    std::vector<int> indices;

    int meshSimplificationIncrement = (levelOfDetail == 0) ? 1 : levelOfDetail * 2;
    int verticesPerLine = (VERTEX_COUNT_PER_LINE - 1) / meshSimplificationIncrement + 1;

    std::vector<float> heightMap(verticesPerLine * verticesPerLine);
    Noise noise;
    noise.GenerateNoiseMap(&heightMap[0], verticesPerLine, verticesPerLine, scale, octaves, persistance, lacunarity, offsetX, offsetY, seed);
    for (int z = 0; z < verticesPerLine; z += meshSimplificationIncrement)
    {
        for (int x = 0; x < verticesPerLine; x += meshSimplificationIncrement)
        {
            vertices.push_back(((float)x / ((float)verticesPerLine - 1.0f))*SIZE);
            float height = heightMap[z * verticesPerLine + x];//perlinNoise.Noise(x/ /*static_cast<float>(VERTEX_COUNT_PER_LINE) * */ 20.0f, z/ /*static_cast<float>(VERTEX_COUNT_PER_LINE) * */20.0f, 10.0f);
            vertices.push_back(height * 20.0f);
            vertices.push_back(((float)z / ((float)verticesPerLine - 1.0f))*SIZE);
            normals.push_back(0.0f);
            normals.push_back(1.0f);
            normals.push_back(0.0f);
            texCoords.push_back((float)x / ((float)verticesPerLine - 1.0f));
            texCoords.push_back((float)z / ((float)verticesPerLine - 1.0f));
        }
    }
    for (int gz = 0; gz < verticesPerLine - 1; gz++)
    {
        for (int gx = 0; gx < verticesPerLine - 1; gx++)
        {
            int topLeft = (gz * verticesPerLine) + gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz + 1) * verticesPerLine + gx);
            int bottomRight = bottomLeft + 1;
            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);
            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }
    rawModel_ = loader.LoadToVAO(*rawModel_, vertices, normals, texCoords, indices);
}

shiny::RawModel * shiny::Terrain::Generate(Loader &loader, float scale, int octaves, float persistance,
                                           float lacunarity, float offsetX, float offsetY, int levelOfDetail, unsigned int seed) {

    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> texCoords;
    std::vector<int> indices;


    int meshSimplificationIncrement = (levelOfDetail == 0) ? 1 : levelOfDetail * 2;
    int verticesPerLine = (VERTEX_COUNT_PER_LINE - 1) / meshSimplificationIncrement + 1;

    std::vector<float> heightMap(verticesPerLine * verticesPerLine);
    Noise noise;
    noise.GenerateNoiseMap(&heightMap[0], verticesPerLine, verticesPerLine, scale, octaves, persistance, lacunarity, offsetX, offsetY, seed);

    int vertexIndex = 0;
    for (int z = 0; z < VERTEX_COUNT_PER_LINE; z += meshSimplificationIncrement)
    {
        for (int x = 0; x < VERTEX_COUNT_PER_LINE; x += meshSimplificationIncrement)
        {
            vertices.push_back(((float)x / ((float)VERTEX_COUNT_PER_LINE - 1.0f))*SIZE);
            float height = heightMap[vertexIndex];
            vertices.push_back(height * 60.0f);
            vertices.push_back(((float)z / ((float)VERTEX_COUNT_PER_LINE - 1.0f))*SIZE);
            normals.push_back(0.0f);
            normals.push_back(1.0f);
            normals.push_back(0.0f);
            texCoords.push_back((float)x / ((float)VERTEX_COUNT_PER_LINE - 1.0f));
            texCoords.push_back((float)z / ((float)VERTEX_COUNT_PER_LINE - 1.0f));

            vertexIndex++;
        }
    }
    for (int gz = 0; gz < verticesPerLine - 1; gz++)
    {
        for (int gx = 0; gx < verticesPerLine - 1; gx++)
        {
            int topLeft = (gz * verticesPerLine) + gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz + 1) * verticesPerLine + gx);
            int bottomRight = bottomLeft + 1;
            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);
            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }
    return loader.LoadToVAO(vertices, normals, texCoords, indices);
}