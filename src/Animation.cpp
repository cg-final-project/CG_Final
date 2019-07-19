#include "Animation.h"

#include "Shadow.h"

AnimationController::AnimationController() {

}

void AnimationController::InitController() {
    AnimationModel *model = new AnimationModel("../../res/model/player/Running.fbx",
                                               glm::vec3(0.005f), glm::vec3(5.0f, 0.8f, 5.0f),
                                               glm::vec3(0.0f, 0.0f, 0.0f));

    animation_models.push_back(model);

    // Init shader
    this->depth_shader = Shader("shadow_mapping_depth_dynamic.vs",
                                "shadow.fs");
    this->shader = Shader("shadow_mapping_dynamic.vs",
                          "shadow_mapping_dynamic.fs");
}

void AnimationController::InitDepthShader(glm::mat4 lightSpaceMatrix) {
    //Shadow map
    this->depth_shader.use();
    this->depth_shader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
}

void AnimationController::InitShader(glm::mat4 lightSpaceMatrix, unsigned int diffuseTexture, unsigned int shadowMap,
                                     glm::vec3 lightPos, glm::vec3 viewPos, glm::mat4 projection, glm::mat4 view) {

    this->shader.use();
    this->shader.setInt("diffuseTexture", diffuseTexture);
    this->shader.setInt("shadowMap", shadowMap);
    this->shader.setVec3("lightPos", lightPos);
    this->shader.setVec3("viewPos", viewPos);
    this->shader.setMat4("projection", projection);
    this->shader.setMat4("view", view);
}

void AnimationController::RenderDepth() {
    for (auto ele : this->animation_models) {
        ele->Draw(this->depth_shader);
    }
}

void AnimationController::Render() {
    for (auto ele : this->animation_models) {
        ele->Draw(this->shader);
    }

}