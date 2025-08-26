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

    void setModelMatrix(glm::mat4 matrix);
    void setProjectionMatrix(glm::mat4 matrix);
    void setViewMatrix(glm::mat4 matrix);
    void setScaleMatrix(glm::mat4 matrix);
    void setTranslationMatrix(glm::mat4 matrix);
    void setObjectColor(glm::vec3 color);
    void setLightColor(glm::vec3 color);
    void setLightPos(glm::vec3 pos);
    void setViewPos(glm::vec3 pos);

    unsigned int getUniformLocation(char *name);

  private:
    std::vector<unsigned int> textures;
    unsigned int viewLoc, modelLoc, projectionLoc, translateLoc, scaleLoc, objectColorLoc, lightColorLoc, lightPosLoc,
        viewPosLoc;

    void setMatrix(unsigned int loc, glm::mat4 mat);
    void setVec3(unsigned int loc, glm::vec3 vec);

    unsigned int createTexture(char *file_path);

    void checkCompileErrors(unsigned int shader, std::string type);
};
#endif
