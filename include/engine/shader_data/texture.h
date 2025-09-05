#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

struct Shader;

class Texture {
  public:
    Texture();
    Texture(const Texture &);

    void applyTexture(Shader &shader);

    std::string getDiffuse() const { return diffuse; }
    std::string getSpecular() const { return specular; }

    void setDiffuse(const std::string texture) { diffuse = texture; }
    void setSpecular(const std::string texture) { specular = texture; }

  private:
    std::string diffuse{};
    std::string specular{};
};

#endif
