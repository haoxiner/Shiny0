//
// Created by haoxin on 17/2/5.
//

#include "EntityRenderer.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

bool shiny::EntityRenderer::Startup(StaticShader *staticShader) {
    staticShader_ = staticShader;
    return true;
}

void shiny::EntityRenderer::Render(std::vector<const Entity*> &entities) {
    for (auto entity : entities) {
		auto model = entity->rawModel_;
		auto material = entity->material_;
		glBindVertexArray(model->GetVAO());
		/*glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, material->GetAlbedoMap());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, material->GetMetallicMap());
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, material->GetRoughnessMap());
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, material->GetNormalMap());*/
        PrepareInstance(*entity);
        glDrawElements(GL_TRIANGLES, model->GetIndicesCount(), GL_UNSIGNED_INT, (void*)0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
    }
}

void shiny::EntityRenderer::PrepareInstance(const Entity &entity) {
    auto transformation = glm::translate(entity.position_);
    transformation = glm::rotate(transformation, entity.rotation_.x, glm::vec3(1,0,0));
    transformation = glm::rotate(transformation, entity.rotation_.y, glm::vec3(0,1,0));
    transformation = glm::rotate(transformation, entity.rotation_.z, glm::vec3(0,0,1));
    transformation = glm::scale(transformation, glm::vec3(entity.scaling_));
    staticShader_->LoadModelMatrix(transformation);
}