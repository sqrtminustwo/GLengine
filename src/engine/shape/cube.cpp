#include <shape.h>
#include <cube.h>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Cube::Cube() {
    setProjectionMatrix(glm::perspective(glm::radians(30.0f), (float)5 / 4, 0.1f, 100.0f));
}

Cube::Cube(const Cube &cube) {
    setVAO(cube.getVAO());
    setVBO(cube.getVBO());
    setModelMatrix(cube.getModelMatrix());
    setProjectionMatrix(cube.getProjectionMatrix());
    setTranslationMatrix(cube.getTranslationMatrix());
}

void Cube::drawShape() {
    glBindVertexArray(getVAO());
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
