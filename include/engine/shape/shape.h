#ifndef SHAPE_H
#define SHAPE_H

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

class Shape {

  public:
    glm::mat4 getModelMatrix() const { return modelMatrix; }
    glm::mat4 getModelNoTranslationMatrix() const;
    glm::mat4 getProjectionMatrix() const { return projectionMatrix; }
    glm::mat4 getTranslationMatrix() const { return translationMatrix; }
    glm::vec3 getPos() const { return pos; }
    float getScaleFactor() const { return scale_factor; }
    glm::vec3 getAmbient() const { return ambient; }
    glm::vec3 getDiffuse() const { return diffuse; }
    glm::vec3 getSpecular() const { return specular; }
    float setShininess() const { return shininess; }

    void setPos(const float x, const float y, const float z);
    void setScale(const float scale_factor);
    void setAmbient(const float r, const float g, const float b) { ambient = glm::vec3(r, g, b); }
    void setAmbient(const glm::vec3 vec) { ambient = vec; }
    void setDiffuse(const float r, const float g, const float b) { diffuse = glm::vec3(r, g, b); }
    void setDiffuse(const glm::vec3 vec) { diffuse = vec; }
    void setSpecular(const float r, const float g, const float b) { specular = glm::vec3(r, g, b); }
    void setSpecular(const glm::vec3 vec) { specular = vec; }
    void setShininess(const float value) { shininess = value; }

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

    glm::vec3 ambient{1.0f};
    glm::vec3 diffuse{1.0f};
    glm::vec3 specular{1.0f};
    float shininess{1.0f};

    glm::vec3 pos{0.0f};
    float scale_factor{1.0f};
    glm::mat4 modelMatrix{1.0f};

    glm::mat4 projectionMatrix{1.0f};
    glm::mat4 translationMatrix{1.0f};
};

#endif
