#ifndef CUBE_H
#define CUBE_H

#include <shape.h>

class Cube : public Shape {
  public:
    Cube();
    Cube(const Cube &);

    float getScaleFactor() const { return scale_factor; }

    void setScale(const float scale_factor);

    void drawShape() override;

  private:
    float scale_factor{1.0f};
};

#endif
