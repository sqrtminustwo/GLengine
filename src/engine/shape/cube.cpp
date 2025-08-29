#include <iostream>
#include <shape.h>
#include <cube.h>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Cube::Cube() {
    setProjectionMatrix(glm::perspective(glm::radians(30.0f), (float)5 / 4, 0.1f, 100.0f));
}

// WARNING: cube can be copied when passing to function
// Keep that in mind when removing things that should be copied (or always pass by reference)
// Removing setting of model matrix can lead to loss of translation/scaling
Cube::Cube(const Cube &cube) {
    setVAO(cube.getVAO());
    setVBO(cube.getVBO());

    setScale(cube.getScaleFactor());
    setProjectionMatrix(cube.getProjectionMatrix());
    setTranslationMatrix(cube.getTranslationMatrix());

    setAmbient(cube.getAmbient());
    setDiffuse(cube.getDiffuse());
    setSpecular(cube.getSpecular());
    setShininess(cube.setShininess());
}

void Cube::drawShape() {
    glBindVertexArray(getVAO());
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
