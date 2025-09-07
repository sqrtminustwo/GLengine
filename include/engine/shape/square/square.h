#ifndef SQUARE_H
#define SQUARE_H

#include <shape_textured.h>
#include <draw_triangles.h>

class Square : public ShapeTextured, private DrawTriangles {
  public:
    Square();

    Square(const Square &);

    void applyShape(Shader &shader) override;
    void drawShape() override;

  private:
    // clang-format off
    static constexpr float vertices[] = {
        // positions                          // normals                       // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
    };
};

#endif
