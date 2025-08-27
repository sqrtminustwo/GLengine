#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
    // Filters the translation from model
    // Position has no effect on direction, translation shouldn't have effect on normal vector
    // Calculation of inverse on GPU is very expensive (better done in code and sent via uniform)
    Normal = mat3(transpose(inverse(modelMatrix))) * aNormal;
    FragPos = vec3(modelMatrix * vec4(aPos, 1.0));

    gl_Position = projectionMatrix * viewMatrix * vec4(FragPos, 1.0);
}
