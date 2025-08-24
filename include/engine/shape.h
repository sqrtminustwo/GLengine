#ifndef SHAPE_H
#define SHAPE_H

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

using mat4 = glm::mat4;
using vec3 = glm::vec3;

class Shape {
  public:
    mat4 getModelMatrix() { return modelMatrix; }
    mat4 getProjectionMatrix() { return projectionMatrix; }
    mat4 getTranslationMatrix() { return translationMatrix; }

    void setPos(float x, float y, float z);

    void setModelMatrix(mat4 matrix) { modelMatrix = matrix; }
    void setProjectionMatrix(mat4 matrix) { projectionMatrix = matrix; }
    void setTranslationMatrix(mat4 matrix) { translationMatrix = matrix; }

    virtual void drawShape() = 0;
    void free_VAO_VBO();

  protected:
    void setVAO(unsigned int VAO) { this->VAO = VAO; }
    void setVBO(unsigned int VBO) { this->VBO = VBO; }

    unsigned int getVAO() { return VAO; }
    unsigned int getVBO() { return VBO; }

  private:
    unsigned int VAO, VBO;

    constexpr static vec3 X{1.0f, 0.0f, 0.0f};
    constexpr static vec3 Y{0.0f, 1.0f, 0.0f};
    constexpr static vec3 Z{0.0f, 0.0f, 0.1f};

    mat4 modelMatrix{1.0f};
    mat4 projectionMatrix{1.0f};
    mat4 translationMatrix{1.0f};
};

#endif
