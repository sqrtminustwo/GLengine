#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 ourColor;

uniform mat4 transform;

float reverse_on_x(float pos) {
    return pos > 0 ? pos - 1 : pos + 1;
}
float abs(float num) {
    return num;
    //return num < 0 ? num * (-1) : num;
}

void main() {
    //    gl_Position = vec4(aPos.x, reverse_on_x(aPos.y), aPos.z, 1.0);
    gl_Position = transform * vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
