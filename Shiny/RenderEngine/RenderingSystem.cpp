//
// Created by haoxin on 17/2/3.
//

#include "RenderingSystem.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

const float shiny::RenderingSystem::FOV = glm::radians(60.0f);
const float shiny::RenderingSystem::NEAR_PLANE = 0.1f;
const float shiny::RenderingSystem::FAR_PLANE = 10000.0f;

bool shiny::RenderingSystem::Startup(float xResolution, float yResolution) {
    float aspectRatio = xResolution / yResolution;
    auto projectionMatrix = glm::perspective(FOV, aspectRatio, NEAR_PLANE, FAR_PLANE);

	// shader: test
    staticShader_.Startup();
    staticShader_.Begin();
    staticShader_.LoadProjectionMatrix(projectionMatrix);
    staticShader_.End();
    entityRenderer_.Startup(&staticShader_);

	// shader: render to screen
	screenShader_.Startup();

	// depth map
	glGenFramebuffers(1, &depthMapFrameBuffer_);
	glGenTextures(1, &depthMap_);
	glBindTexture(GL_TEXTURE_2D, depthMap_);
	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_DEPTH_COMPONENT,
				 static_cast<int>(xResolution),
				 static_cast<int>(yResolution),
				 0,
				 GL_DEPTH_COMPONENT,
				 GL_FLOAT,
				 nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFrameBuffer_);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap_, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// quad
	glGenVertexArrays(1, &quadVAO_);
	glBindVertexArray(quadVAO_);
	glGenBuffers(1, &quadPositionVBO_);
	glBindBuffer(GL_ARRAY_BUFFER, quadPositionVBO_);
	float quadPosition[] = {
		-1.0f, 1.0f,// 0: top left
		-1.0f, -1.0f,// 1: bottom left
		1.0f, 1.0f,// 2: top right
		1.0f, -1.0f// 3: bottom right
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadPosition), quadPosition, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glGenBuffers(1, &quadTexCoordVBO_);
	glBindBuffer(GL_ARRAY_BUFFER, quadTexCoordVBO_);
	float quadTexCoord[] = {
		0.0f, 1.0f,// 0: top left
		0.0f, 0.0f,// 1: bottom left
		1.0f, 1.0f,// 2: top right
		1.0f, 0.0f// 3: bottom right
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadTexCoord), quadTexCoord, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

    return true;
}

void shiny::RenderingSystem::Process(const Entity *entity) {
    entities_.push_back(entity);
}

void shiny::RenderingSystem::Prepare() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void shiny::RenderingSystem::Render(const Light &light, const Camera &camera) {
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFrameBuffer_);
	glClear(GL_DEPTH_BUFFER_BIT);
    staticShader_.Begin();
    //staticShader_.LoadLight(light);
    staticShader_.LoadViewMatrix(camera);
    entityRenderer_.Render(entities_);
    staticShader_.End();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	screenShader_.Begin();
	glBindVertexArray(quadVAO_);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, depthMap_);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	screenShader_.End();
}