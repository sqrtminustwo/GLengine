#include <texture.h>
#include <shader.h>

Texture::Texture() {}

Texture::Texture(const Texture &other) {
    setDiffuse(other.getDiffuse());
    setSpecular(other.getSpecular());
    setEmission(other.getEmission());
}

void Texture::applyTexture(Shader &shader) {
    if (!diffuse.empty()) shader.useDiffuseTexture(diffuse);
    if (!specular.empty()) shader.useSpecualarTexture(specular);
    if (!emission.empty()) {
        shader.useEmissionTexture(emission);
        shader.setBool(Shader::MATERIAL_HAS_EMISSION, true);
    } else
        shader.setBool(Shader::MATERIAL_HAS_EMISSION, false);
}
