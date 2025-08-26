#include <shape.h>
#include <glad.h>
#include <GLFW/glfw3.h>

void Shape::free_VAO_VBO() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Shape::setPos(float x, float y, float z) {
    pos = glm::vec3(x, y, z);
    glm::mat4 translationMatrix{1.0f};
    translationMatrix = glm::translate(translationMatrix, pos);
    setTranslationMatrix(translationMatrix);
}
