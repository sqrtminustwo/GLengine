#ifndef SHAPE_TEXTURED_H
#define SHAPE_TEXTURED_H

#include <shape.h>
#include <string>

class ShapeTextured : public Shape {
  public:
    ShapeTextured();
    ShapeTextured(const ShapeTextured &);
    void applyTexturedShape(Shader &shader);

    std::string getDiffuse() const { return diffuse; }
    std::string getSpecular() const { return specular; }

    void setDiffuse(const std::string texture) { diffuse = texture; }
    void setSpecular(const std::string texture) { specular = texture; }

  private:
    std::string diffuse{};
    std::string specular{};
};

#endif
