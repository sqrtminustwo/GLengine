#include <shader.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <vector>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void Shader::setMatrix(unsigned int loc, glm::mat4 mat) {
    use();
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}
void Shader::setModelMatrix(glm::mat4 matrix) { setMatrix(modelLoc, matrix); }
void Shader::setProjectionMatrix(glm::mat4 matrix) { setMatrix(projectionLoc, matrix); }
void Shader::setViewMatrix(glm::mat4 matrix) { setMatrix(viewLoc, matrix); }
void Shader::setScaleMatrix(glm::mat4 matrix) { setMatrix(scaleLoc, matrix); }
void Shader::setTranslationMatrix(glm::mat4 matrix) { setMatrix(translateLoc, matrix); }

void Shader::setLightingColor(float r, float g, float b) { glUniform3f(lightingLoc, r, g, b); }

unsigned int Shader::getUniformLocation(char *name) { return glGetUniformLocation(ID, name); }

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure &e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    viewLoc = getUniformLocation("viewMatrix");
    modelLoc = getUniformLocation("modelMatrix");
    projectionLoc = getUniformLocation("projectionMatrix");
    translateLoc = getUniformLocation("translate");
    scaleLoc = getUniformLocation("scaleDown");
    lightingLoc = getUniformLocation("lightColor");

    glEnable(GL_DEPTH_TEST);
}

void Shader::destruct() { glDeleteProgram(ID); }

void Shader::use() {
    glUseProgram(ID);
    // Use textures
    for (int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures.at(i));
    }
}

void Shader::loadTexture(char *path) {
    try {
        unsigned int texture = createTexture(path);
        unsigned int texture_num = textures.size();
        char texture_name[9] = "texture ";
        texture_name[7] = texture_num + '0';
        use();
        glUniform1i(getUniformLocation(texture_name), texture_num);
        textures.push_back(texture);
    } catch (std::exception ex) {
        std::cerr << "Error loading texture: " << std::endl;
        std::cerr << ex.what() << std::endl;
        throw;
    }
}

unsigned int Shader::createTexture(char *file_path) {
    static std::map<int, GLenum> color_formats{{1, GL_RED}, {3, GL_RGB}, {4, GL_RGBA}};
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(file_path, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (color_formats.count(nrChannels))
            format = color_formats[nrChannels];
        else {
            std::cerr << "Unsupported number of channels: " << nrChannels << " for " << file_path << std::endl;
            stbi_image_free(data);
            throw std::runtime_error("Image color type is unsupported.");
        }
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        throw std::runtime_error("Failed to load image.");
    }
    stbi_image_free(data);

    return texture;
}

void Shader::checkCompileErrors(unsigned int shader, std::string type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                      << infoLog
                      << "\n -- "
                         "--------------------------------------------------- -- "
                      << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                      << infoLog
                      << "\n -- "
                         "--------------------------------------------------- -- "
                      << std::endl;
        }
    }
}
