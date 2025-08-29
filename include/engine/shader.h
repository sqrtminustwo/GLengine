#ifndef SHADER_H
#define SHADER_H

#include <glm/ext/matrix_float4x4.hpp>
#include <vector>
#include <string>

class Shader {
  public:
    unsigned int ID;

    Shader(const char *vertexPath, const char *fragmentPath);

    void destruct();

    void use();

    void loadTexture(char *path);

    void setModelMatrix(const glm::mat4 matrix);
    void setModelNoTranslationMatrix(const glm::mat4 matrix);
    void setProjectionMatrix(const glm::mat4 matrix);
    void setViewMatrix(const glm::mat4 matrix);

    void setObjectColor(const glm::vec3 color);
    void setLightColor(const glm::vec3 color);
    void setLightPos(const glm::vec3 pos);
    void setViewPos(const glm::vec3 pos);

    void setAmbient(const glm::vec3 vec);
    void setDiffuse(const glm::vec3 vec);
    void setSpecular(const glm::vec3 vec);
    void setShininess(const float value);

    unsigned int getUniformLocation(const char *name);

  private:
    std::vector<unsigned int> textures;
    unsigned int viewLoc, modelLoc, modelNoTranslationLoc, projectionLoc, objectColorLoc,
        lightColorLoc, lightPosLoc, viewPosLoc, ambientLoc, diffuseLoc, specularLoc, shininessLoc;

    void setMat4(const unsigned int loc, const glm::mat4 mat);
    void setVec3(const unsigned int loc, const glm::vec3 vec);
    void setFloat(const unsigned int loc, const float num);

    const unsigned int createTexture(const char *file_path);

    void checkCompileErrors(const unsigned int shader, const std::string type) const;
};
#endif
