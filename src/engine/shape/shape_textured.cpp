#include <shape_textured.h>
#include <shader.h>

ShapeTextured::ShapeTextured() : Shape() {}
ShapeTextured::ShapeTextured(const ShapeTextured &other) : Shape(other), Texture(other) {}

void ShapeTextured::applyTexturedShape(Shader &shader) {
    applyTexture(shader);
    applyBaseShape(shader);
}
