#include <glad.h>
#include <GLFW/glfw3.h>
#include <shape.h>
#include <shader.h>

// WARNING: cube can be copied when passing to function
// Keep that in mind when removing things that should be copied (or always pass by reference)
// Removing setting of model matrix can lead to loss of translation/scaling
Shape::Shape(const Shape &other) {
    setVAO(other.getVAO());
    setVBO(other.getVBO());
    setIBO(other.getIBO());

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
