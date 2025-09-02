// // GLSL version (OpenGL 3.3)
// #version 330
//
// // uniforms
// uniform vec4 lightPosition; // should be in the eye space
// uniform vec4 lightAmbient; // light ambient color
// uniform vec4 lightDiffuse; // light diffuse color
// uniform vec4 lightSpecular; // light specular color
// uniform vec4 materialAmbient; // material ambient color
// uniform vec4 materialDiffuse; // material diffuse color
// uniform vec4 materialSpecular; // material specular color
// uniform float materialShininess; // material specular shininess
// uniform sampler2D map0; // texture map #1
// uniform bool textureUsed; // flag for texture
//
// struct Material {
//     sampler2D diffuse;
//     sampler2D specular;
//     float shininess;
// };
// uniform Material material;
//
// struct Light {
//     vec3 position;
//
//     vec3 ambient;
//     vec3 diffuse;
//     vec3 specular;
// };
// uniform Light light;
//
// // varyings (input)
// in vec3 esVertex;
// in vec3 esNormal;
// in vec2 texCoord0;
//
// // output
// out vec4 fragColor;
//
// void main() {
//     vec3 normal = normalize(esNormal);
//     vec3 light;
//     if (lightPosition.w == 0.0) {
//         light = normalize(lightPosition.xyz);
//     } else {
//         light = normalize(lightPosition.xyz - esVertex);
//     }
//     vec3 view = normalize(-esVertex);
//     vec3 reflectVec = reflect(-light, normal); // 2 * N * (N dot L) - L
//
//     vec3 color = (light.ambient).rgb * (material.ambient).rgb; // begin with ambient
//     float dotNL = max(dot(normal, light), 0.0);
//     color += (light.diffuse).rgb * (material.diffuse).rgb * dotNL; // add diffuse
//     if (textureUsed)
//         color *= texture(map0, texCoord0).rgb; // modulate texture map
//     float dotVR = max(dot(view, reflectVec), 0.0);
//     color += pow(dotVR, material.shininess) * (light.specular).rgb * (material.specular).rgb; // add specular
//     fragColor = vec4(color, (material.diffuse).a); // set frag color
// }

#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform vec3 viewPos;

void main() {
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // vec3 specular = light.specular * (spec * vec3(0.5, 0.5, 0.5));
    vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
