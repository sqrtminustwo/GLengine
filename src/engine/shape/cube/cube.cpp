#include <shape.h>
#include <cube.h>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Cube::Cube() : Shape() {}

void Cube::drawShape() {
    glBindVertexArray(getVAO());
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
