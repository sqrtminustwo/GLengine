#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

uniform vec3 lightColor;

void main() {
    FragColor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.5);

    float ambientStrength = 0.1;
    FragColor *= vec4(lightColor, 1.0) * ambientStrength;
}
