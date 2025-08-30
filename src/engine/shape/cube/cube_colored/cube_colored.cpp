#include <shader.h>
#include <cube_colored.h>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

CubeColored::CubeColored() {
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // Normal (perpendecular line for each triangle, written by hand KEK)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    setVAO(VAO);
    setVBO(VBO);
}

CubeColored::CubeColored(const CubeColored &other) : Cube(other) {
    setColor(other.getColor());
    setAmbient(other.getAmbient());
    setDiffuse(other.getDiffuse());
    setSpecular(other.getSpecular());
    setShininess(other.setShininess());
}

void CubeColored::applyShape(Shader &shader) {
    shader.setVec3(Shader::OBJECT_COLOR, color);
    shader.setVec3(Shader::MATERIAL_AMBIENT, ambient);
    shader.setVec3(Shader::MATERIAL_DIFFUSE, diffuse);
    shader.setVec3(Shader::MATERIAL_SPECULAR, specular);
    shader.setFloat(Shader::MATERIAL_SHININESS, shininess);

    applyShapeBase(shader);
}
