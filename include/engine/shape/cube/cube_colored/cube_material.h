#ifndef CUBE_MATERIAL_H
#define CUBE_MATERIAL_H

#include <cube_colored.h>

class CubeMaterial : public CubeColored {
  public:
    CubeMaterial();
    CubeMaterial(const CubeMaterial &other);

    void applyShape(Shader &shader) override;

    float getShininess() const { return shininess; }

    void setShininess(const float value) { shininess = value; }

  private:
    float shininess{1.0f};
};

#endif
