#include <shape.h>
#include <glad.h>
#include <GLFW/glfw3.h>

void Shape::destruct() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
