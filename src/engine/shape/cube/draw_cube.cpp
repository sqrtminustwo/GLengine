#include <glad.h>
#include <draw_cube.h>

void DrawCube::drawCube(unsigned int VAO) {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
