#include <shape.h>
#include <cube.h>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Cube::Cube() {
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    setVAO(VAO);
    setVBO(VBO);

    setModelMatrix(mat4(1.0f));
    setProjectionMatrix(glm::perspective(glm::radians(30.0f), (float)5 / 4, 0.1f, 100.0f));
}

Cube::Cube(Cube &cube) {
    setVAO(cube.getVAO());
    setVBO(cube.getVBO());
    setModelMatrix(cube.getModelMatrix());
    setProjectionMatrix(cube.getProjectionMatrix());
    setTranslationMatrix(cube.getTranslationMatrix());
}

void Cube::drawShape() {
    glBindVertexArray(getVAO());
    glDrawArrays(GL_TRIANGLES, 0, 36);
    setModelMatrix(mat4(1.0f));
}
