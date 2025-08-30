#include <cube_material.h>
#include <shader.h>

CubeMaterial::CubeMaterial() : CubeColored() {}

CubeMaterial::CubeMaterial(const CubeMaterial &other) : CubeColored(other) {
    setShininess(other.getShininess());
}

void CubeMaterial::applyShape(Shader &shader) {
    shader.setFloat(Shader::MATERIAL_SHININESS, shininess);
    applyColoredShape(shader);
}
