#include <shape.h>
#include <cube.h>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Cube::Cube() {
    setProjectionMatrix(glm::perspective(glm::radians(30.0f), (float)5 / 4, 0.1f, 100.0f));
}

Cube::Cube(const Cube &other) : Shape(other) { setScale(other.getScaleFactor()); }

void Cube::drawShape() {
    glBindVertexArray(getVAO());
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Cube::setScale(const float scale_factor) {
    setModelMatrix(glm::scale(getModelMatrix(), glm::vec3{1 / this->scale_factor}));
    this->scale_factor = scale_factor;
    setModelMatrix(glm::scale(getModelMatrix(), glm::vec3{this->scale_factor}));
}
