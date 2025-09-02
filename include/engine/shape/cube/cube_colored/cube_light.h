#ifndef CUBE_LIGHT_H
#define CUBE_LIGHT_H

#include <cube_colored.h>

class CubeLight : public CubeColored {
  public:
    CubeLight();
    void applyShape(Shader &) override;
    void applyLight(Shader &);
};

#endif
