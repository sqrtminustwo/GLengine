#ifndef SHADER_H
#define SHADER_H

#include <glad.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <vector>
#include <string>

class Shader {
  public:
    unsigned int ID;

    Shader(const char *vertexPath, const char *fragmentPath);

    void destruct();

    void use();

    void loadTexture(char *path);

    void setModelMatrix(glm::mat4 matrix) { glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(matrix)); }
    void setProjectionMatrix(glm::mat4 matrix) {
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(matrix));
    }
    void setViewMatrix(glm::mat4 matrix) { glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(matrix)); }
    void setScaleMatrix(glm::mat4 matrix) { glUniformMatrix4fv(scaleLoc, 1, GL_FALSE, glm::value_ptr(matrix)); }
    void setTranslationMatrix(glm::mat4 matrix) {
        glUniformMatrix4fv(translateLoc, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    unsigned int getUniformLocation(char *name) { return glGetUniformLocation(ID, name); }

  private:
    std::map<int, GLenum> color_formats{{1, GL_RED}, {3, GL_RGB}, {4, GL_RGBA}};
    std::vector<unsigned int> textures;
    unsigned int viewLoc, modelLoc, projectionLoc, translateLoc, scaleLoc;

    unsigned int createTexture(char *file_path);

    void checkCompileErrors(unsigned int shader, std::string type);
};
#endif
