#ifndef TEXT_H
#define TEXT_H

#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_int2.hpp>
#include <map>
#include <string>
#include <shader.h>

struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2 Size;        // Size of glyph
    glm::ivec2 Bearing;     // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class Text {
  public:
    Text(Shader shader);

    void renderText(Shader shader, std::string text, float x, float y, float scale, glm::vec3 color);

  private:
    std::map<char, Character> Characters;
    unsigned int VAO, VBO;
};

#endif
