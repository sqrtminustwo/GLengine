#include <glad.h>
#include <draw_triangles.h>

void DrawTriangles::drawCube(unsigned int VAO, const int vertices_size) {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices_size);
}
