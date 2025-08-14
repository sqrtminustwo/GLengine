#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aTexCoord;

out vec2 TexCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform mat4 scaleDown;
uniform mat4 translate;

void main() {
    gl_Position = translate * vec4(aPos, 1.0);
    gl_Position = scaleDown * gl_Position;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * gl_Position;
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
