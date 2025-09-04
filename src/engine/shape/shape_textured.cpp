#include <shape_textured.h>
#include <shader.h>

ShapeTextured::ShapeTextured() : Shape() {}
ShapeTextured::ShapeTextured(const ShapeTextured &other) : Shape(other) {
    diffuse = other.getDiffuse();
    specular = other.getSpecular();
}

void ShapeTextured::applyTexturedShape(Shader &shader) {
    if (!diffuse.empty()) shader.useDiffuseTexture(diffuse);
    if (!specular.empty()) shader.useSpecualarTexture(specular);
    applyBaseShape(shader);
}
