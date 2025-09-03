#ifndef CUBE_H
#define CUBE_H

#include <shape.h>

class Cube : public Shape {
  public:
    Cube();

    void drawShape() override;
};

#endif
