#include <light.h>
#include <shader.h>

void Light::applyLight(Shader &shader) {
    shader.setVec3(Shader::LIGHT_AMBIENT, ambient);
    shader.setVec3(Shader::LIGHT_DIFFUSE, diffuse);
    shader.setVec3(Shader::LIGHT_SPECULAR, specular);
}
