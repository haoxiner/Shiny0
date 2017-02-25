#include "RenderEngine/Display.h"
#include "RenderEngine/loader.h"
#include "RenderEngine/staticshader.h"
#include "RenderEngine/RenderingSystem.h"
#include "RenderEngine/EntityRenderer.h"
#include "Entity/entity.h"
#include "Entity/camera.h"
#include "Entity/player.h"
#include "glm/gtx/transform.hpp"
#include "opengl.h"
#include "Model/ObjLoader.h"
#include "RenderEngine/PerformanceTimer.h"
#include <vector>
#include <string>
#include <iostream>
#include <Model/ObjLoader.h>

#undef main

int main()
{
    const int xResolution = 800;
    const int yResolution = 600;

    shiny::Display display;
    if (!display.Startup(xResolution, yResolution)) {
        return 1;
    }
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glClearColor(0.0,0.0,0.0,1.0);

    std::vector<float> positions = {
            0.0f,1.0f,0.0f,
            0.0f,0.0f,-1.0f,
            0.7f,0.0f,0.7f,
            -0.7f,0.0f,0.7f
    };
    std::vector<float> normals = {
            0.0f,1.0f,0.0f,
            0.0f,0.0f,-1.0f,
            0.7f,0.0f,0.7f,
            -0.7f,0.0f,0.7f
    };
    std::vector<float> texCoords = {
            0.5f, 1.f - 1.0f,
            0.0f, 1.f - 0.0f,
            1.0f, 1.f - 0.0f,
            0.5f, 0.5f
    };
    std::vector<int> indices = {
            0,3,2,
            0,2,1,
            0,1,3,
            1,2,3
    };

    std::vector<shiny::Entity> entities;

    // obj
    std::string inputfile = "Resource/crytek-sponza/sponza.obj";
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;
    bool ret = tinyobj::LoadObj(shapes, materials, err, inputfile.c_str());

    shiny::Loader loader;
    shiny::RawModel *rawModel = loader.LoadToVAO(positions, normals, texCoords, indices);
	shiny::PBRMaterial floorMaterial(loader.LoadTexture("Resource/sponza_floor_diff.DDS"),
									 loader.LoadTexture("Resource/sponza_floor_metallic.DDS"),
									 loader.LoadTexture("Resource/sponza_floor_roughness.DDS"),
									 loader.LoadTexture("Resource/Sponza_Floor_normal.DDS"));

    for (auto &&shape : shapes) {
        std::vector<int> indices;
        for (auto index : shape.mesh.indices) {
            indices.push_back(index);
        }
        shiny::RawModel *rawModel = loader.LoadToVAO(shape.mesh.positions, shape.mesh.normals, shape.mesh.texcoords, indices);
		entities.emplace_back(rawModel, &floorMaterial, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
    }
	shiny::Player player(rawModel, &floorMaterial, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 10.0f);

    /*
    float scale = 26.0f;
    int octaves = 4;
    float persistance = 0.5f;
    float lacunarity = 2;
    float offsetX = 0;
    float offsetY = 0;
    shiny::Terrain *terrain = new shiny::Terrain(0,0,&floorTexture,loader, scale, octaves, persistance, lacunarity, offsetX, offsetY, 0, 0);
     */
    shiny::Camera camera;
    shiny::Light light;

    shiny::RenderingSystem masterRenderer;
    masterRenderer.Startup(xResolution, yResolution);
    masterRenderer.Process(&player);
    for (auto &&entity : entities) {
        masterRenderer.Process(&entity);
    }
    auto input = display.GetInput();

    float deltaTime = 0.0f;

    shiny::PerformanceTimer performanceTimer;

    performanceTimer.Reset();
    while (display.Running()) {
        performanceTimer.Tick();
        deltaTime = performanceTimer.GetDeltaTime();
        player.Update(deltaTime, input);
        camera.Update(deltaTime, input, &player);
        masterRenderer.Prepare();
        masterRenderer.Render(light, camera);
        display.Update();
        if (input->Quit()) {
            display.Shutdown();
        }
    }
    return 0;
}