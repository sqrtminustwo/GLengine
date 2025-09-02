#ifndef CUBE_MATERIAL_H
#define CUBE_MATERIAL_H

#include <cube_colored.h>

class CubeMaterial : public CubeColored {
  public:
    CubeMaterial();
    CubeMaterial(const CubeMaterial &);

    void applyShape(Shader &) override;
};

#endif
