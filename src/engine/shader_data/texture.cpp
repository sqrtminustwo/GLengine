#include <texture.h>
#include <shader.h>

Texture::Texture() {}

Texture::Texture(const Texture &other) {
    setDiffuse(other.getDiffuse());
    setSpecular(other.getSpecular());
}

void Texture::applyTexture(Shader &shader) {
    if (!diffuse.empty()) shader.useDiffuseTexture(diffuse);
    if (!specular.empty()) shader.useSpecualarTexture(specular);
}
