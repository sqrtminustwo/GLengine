#include <cube_light.h>
#include <shader.h>

CubeLight::CubeLight() : CubeColored() {}

void CubeLight::applyShape(Shader &shader) { applyColoredShape(shader); }

void CubeLight::applyLight(Shader &shader) {
    shader.setVec3(Shader::LIGHT_AMBIENT, getAmbient());
    shader.setVec3(Shader::LIGHT_DIFFUSE, getDiffuse());
    shader.setVec3(Shader::LIGHT_SPECULAR, getSpecular());
}
