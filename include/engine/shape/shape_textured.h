#ifndef SHAPE_TEXTURED_H
#define SHAPE_TEXTURED_H

#include <shape.h>
#include <texture.h>

class ShapeTextured : public Shape, public Texture {
  public:
    ShapeTextured();
    ShapeTextured(const ShapeTextured &);
    void applyTexturedShape(Shader &shader);
};

#endif
