#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <shape.h>
#include <shader.h>

Shape::Shape() {
    setProjectionMatrix(glm::perspective(glm::radians(30.0f), (float)5 / 4, 0.1f, 100.0f));
}
// WARNING: cube can be copied when passing to function
// Keep that in mind when removing things that should be copied (or always pass by reference)
// Removing setting of model matrix can lead to loss of translation/scaling
Shape::Shape(const Shape &other) {
    setVAO(other.getVAO());
    setVBO(other.getVBO());
    setIBO(other.getIBO());

    setScale(other.getScaleFactor());
    setShininess(other.getShininess());
    setProjectionMatrix(other.getProjectionMatrix());
    setTranslationMatrix(other.getTranslationMatrix());
}

void Shape::applyBaseShape(Shader &shader) {
    shader.setMat4(Shader::MODEL_MAT, modelMatrix);
    shader.setMat4(Shader::MODEL_NO_TRANSLATION_MAT, getModelNoTranslationMatrix());
    shader.setMat4(Shader::PROJECTION_MAT, projectionMatrix);
    shader.setFloat(Shader::MATERIAL_SHININESS, shininess);
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
    setModelMatrix(glm::scale(getModelMatrix(), glm::vec3{1 / this->scale_factor}));
    this->scale_factor = scale_factor;
    setModelMatrix(glm::scale(getModelMatrix(), glm::vec3{this->scale_factor}));
}
