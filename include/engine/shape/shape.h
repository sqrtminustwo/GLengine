#ifndef SHAPE_H
#define SHAPE_H

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

class Shape {

  public:
    glm::mat4 getModelMatrix() const { return modelMatrix; }
    glm::mat4 getProjectionMatrix() const { return projectionMatrix; }
    glm::mat4 getTranslationMatrix() const { return translationMatrix; }
    glm::vec3 getPos() const { return pos; }
    float getScaleFactor() const { return scale_factor; }

    void setPos(const float x, const float y, const float z);
    void setScale(const float scale_factor);

    virtual void drawShape() = 0;
    void free_VAO_VBO();

  protected:
    void setModelMatrix(const glm::mat4 matrix) { modelMatrix = matrix; }
    void setProjectionMatrix(const glm::mat4 matrix) { projectionMatrix = matrix; }
    void setTranslationMatrix(const glm::mat4 matrix) { translationMatrix = matrix; }

    void setVAO(const unsigned int VAO) { this->VAO = VAO; }
    void setVBO(const unsigned int VBO) { this->VBO = VBO; }

    unsigned int getVAO() const { return VAO; }
    unsigned int getVBO() const { return VBO; }

    constexpr static glm::vec3 X{1.0f, 0.0f, 0.0f};
    constexpr static glm::vec3 Y{0.0f, 1.0f, 0.0f};
    constexpr static glm::vec3 Z{0.0f, 0.0f, 0.1f};

  private:
    unsigned int VAO, VBO;

    glm::vec3 pos{0.0f};
    float scale_factor{1.0f};
    glm::mat4 modelMatrix{1.0f};

    glm::mat4 projectionMatrix{1.0f};
    glm::mat4 translationMatrix{1.0f};
};

#endif
