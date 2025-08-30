#ifndef CUBE_LIGHT_H
#define CUBE_LIGHT_H

#include <cube_colored.h>

class CubeLight : public CubeColored {
  public:
    CubeLight();
    void applyShape(Shader &shader) override;
    void applyLight(Shader &shader);
};

#endif
