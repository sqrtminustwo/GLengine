#ifndef SHAPE_H
#define SHAPE_H

#include <glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using mat4 = glm::mat4;
using vec3 = glm::vec3;

class Shape {
  public:
    mat4 getModelMatrix() { return modelMatrix; }
    mat4 getProjectionMatrix() { return projectionMatrix; }

    virtual void drawShape() = 0;
    void destruct() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

  protected:
    void setVAO(unsigned int VAO) { this->VAO = VAO; }
    void setVBO(unsigned int VBO) { this->VBO = VBO; }

    unsigned int getVAO() { return VAO; }
    unsigned int getVBO() { return VBO; }

    void setModelMatrix(mat4 matrix) { modelMatrix = matrix; }
    void setProjectionMatrix(mat4 matrix) { projectionMatrix = matrix; }

  private:
    unsigned int VAO, VBO;

    constexpr static vec3 X = vec3(1.0f, 0.0f, 0.0f);
    constexpr static vec3 Y = vec3(0.0f, 1.0f, 0.0f);
    constexpr static vec3 Z = vec3(0.0f, 0.0f, 0.1f);

    mat4 modelMatrix;
    mat4 projectionMatrix;
};

#endif
