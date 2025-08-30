#include <glad.h>
#include <GLFW/glfw3.h>
#include <shape.h>
#include <shader.h>

void Shape::applyShapeBase(Shader &shader) {
    shader.setMat4(Shader::MODEL_MAT, modelMatrix);
    shader.setMat4(Shader::MODEL_NO_TRANSLATION_MAT, getModelNoTranslationMatrix());
    shader.setMat4(Shader::PROJECTION_MAT, projectionMatrix);
}

void Shape::free_VAO_VBO() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

glm::mat4 Shape::getModelNoTranslationMatrix() const {
    glm::mat4 modelNoTranslation = modelMatrix;
    return glm::transpose(glm::inverse(modelNoTranslation));
}

void Shape::setPos(const float x, const float y, const float z) {
    modelMatrix = glm::translate(modelMatrix, glm::vec3{-pos.x, -pos.y, -pos.z});
    pos = glm::vec3(x, y, z);
    modelMatrix = glm::translate(modelMatrix, glm::vec3{pos.x, pos.y, pos.z});
}

void Shape::setScale(const float scale_factor) {
    modelMatrix = glm::scale(modelMatrix, glm::vec3{1 / this->scale_factor});
    this->scale_factor = scale_factor;
    modelMatrix = glm::scale(modelMatrix, glm::vec3{this->scale_factor});
}
