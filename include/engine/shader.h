#ifndef SHADER_H
#define SHADER_H

#include <glm/ext/matrix_float4x4.hpp>
#include <map>
#include <string>
#include <array>

class Shader {
  public:
    // Not meant to do VALUE = ..., so using last variable as SIZE stays safe
    enum UniformType {
        VIEW_MAT,
        MODEL_MAT,
        MODEL_NO_TRANSLATION_MAT,
        PROJECTION_MAT,
        VIEW_POS,
        LIGHT_POS,
        LIGHT_AMBIENT,
        LIGHT_DIFFUSE,
        LIGHT_SPECULAR,
        MATERIAL_AMBIENT,
        MATERIAL_DIFFUSE,
        MATERIAL_SPECULAR,
        MATERIAL_SHININESS,
        SIZE
    };

    Shader(const std::string vertexPath, const std::string fragmentPath);

    void destruct();

    void use();

    void loadDiffuseTexture(const std::string path);
    void loadSpecualarTexture(const std::string path);

    void setMat4(UniformType, const glm::mat4);
    void setVec3(UniformType, const glm::vec3);
    void setFloat(UniformType, const float);

    unsigned int getUniformLocation(const std::string name);

  private:
    unsigned int ID;

    std::array<unsigned int, SIZE> uniforms;
    std::map<std::string, unsigned int> textures;

    void loadTexture(const std::string path, const UniformType name);
    const unsigned int createTexture(const std::string file_path);

    void checkCompileErrors(const unsigned int shader, const std::string type) const;
};

#endif
