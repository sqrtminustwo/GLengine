#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform mat4 scaleDown;
uniform mat4 translate;

void main() {
    gl_Position = translate * vec4(aPos, 1.0);
    gl_Position = scaleDown * gl_Position;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * gl_Position;

    // Filters the translation from model
    // Position has no effect on direction, translation shouldn't have effect on normal vector
    // Calculation of inverse on GPU is very expensive (better done in code and sent via uniform)
    Normal = mat3(transpose(inverse(modelMatrix))) * aNormal;
    FragPos = vec3(modelMatrix * vec4(aPos, 1.0));
}
