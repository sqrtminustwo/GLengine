#include <glad.h>
#include <GLFW/glfw3.h>
#include "sphere.h"
#include <cube_textured.h>
#include <cube_light.h>
#include <cube_material.h>
#include <iostream>
#include <window.h>
#include <camera.h>
#include <input.h>
#include <shader.h>
#include <stats.h>
#include <plot.h>

using triplet = std::tuple<float, float, float>;
using cube_type = CubeTextured;
using cube_ptr = std::unique_ptr<cube_type>;

void genAndAddCubes(
    const cube_type &cube_template, std::vector<cube_ptr> &cubes,
    const std::vector<triplet> &&coords, const triplet &left_bottom_corner
) {
    for (auto coord : coords) {
        std::unique_ptr<cube_type> cube(new cube_type{cube_template});
        auto [base_x, base_y, base_z] = left_bottom_corner;
        auto [x, y, z] = coord;
        cube->setPos(base_x + x, base_y + y, base_z + z);
        cubes.push_back(std::move(cube));
    }
}

int main() {
    Window window{1280, 1000, std::tuple(0, 0, 0, 0.7)};
    Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};
    Input input(&camera, &window);

    Shader sphere_shader(
        PROJECT_DIR "/resources/shaders/shape/sphere/vertex_shader.glsl",
        PROJECT_DIR "/resources/shaders/shape/sphere/fragment_shader.glsl"
    );
    Shader cube_shader(
        PROJECT_DIR "/resources/shaders/shape/cube/textured/vertex_shader.glsl",
        PROJECT_DIR "/resources/shaders/shape/cube/textured/fragment_shader.glsl"
    );
    Shader lighting_shader(
        PROJECT_DIR "/resources/shaders/shape/cube/lighting/vertex_shader.glsl",
        PROJECT_DIR "/resources/shaders/shape/cube/lighting/fragment_shader.glsl"
    );

    constexpr float scaleFactor = 0.1f;

    Sphere sphere(0.5f);
    sphere.setDiffuse(PROJECT_DIR "/resources/textures/moon.png");

    cube_type cube_template{};
    cube_template.setScale(scaleFactor);
    cube_template.setDiffuse(PROJECT_DIR "/resources/textures/container.png");
    cube_template.setSpecular(PROJECT_DIR "/resources/textures/container_specular.png");
    cube_template.setShininess(10.0f);
    std::vector<cube_ptr> cubes;

    CubeLight cube_light{};
    cube_light.setScale(scaleFactor);
    cube_light.setAmbient(0.2f, 0.2f, 0.2f);
    cube_light.setDiffuse(0.5f, 0.5f, 0.5f);
    cube_light.setSpecular(1.0f, 1.0f, 1.0f);
    constexpr auto size = 10;
    constexpr auto middle = size / 2;
    triplet left_bottom_corner{middle, middle, middle};

    constexpr auto radius = 10;
    cube_light.setPos(radius, radius, 0);

    for (float i = 0; i <= size; i++) {
        genAndAddCubes(
            cube_template,
            cubes,
            {{-i, 0.0f, 0.0f}, {-i, -size, 0.0f}, {-i, 0.0f, -size}, {-i, -size, -size}},
            left_bottom_corner
        );

        genAndAddCubes(
            cube_template,
            cubes,
            {{0.0f, -i, 0.0f}, {-size, -i, 0.0f}, {0.0f, -i, -size}, {-size, -i, -size}},
            left_bottom_corner
        );

        genAndAddCubes(
            cube_template,
            cubes,
            {{0.0f, 0.0f, -i}, {0.0f, -size, -i}, {-size, 0.0f, -i}, {-size, -size, -i}},
            left_bottom_corner
        );
    }

    // Stats stats{};
    // stats.start(); // End is defined in class destructor

    while (!glfwWindowShouldClose(window.getWindow())) {
        // stats.updateFps();

        input.processInput();

        window.clearScreen();

        lighting_shader.setMat4(Shader::VIEW_MAT, camera.getViewMatrix());
        auto time = glfwGetTime();
        auto x = radius * std::cos(time);
        auto y = radius * std::sin(time);
        auto z = 0;
        cube_light.setPos(x, y, y);
        cube_light.applyShape(lighting_shader);
        cube_light.drawShape();

        cube_shader.setVec3(Shader::LIGHT_POS, cube_light.getPos());
        cube_shader.setMat4(Shader::VIEW_MAT, camera.getViewMatrix());
        cube_shader.setVec3(Shader::VIEW_POS, camera.getPosition());

        cube_light.applyLight(cube_shader);
        cube_template.applyShape(cube_shader);
        cube_template.drawShape();
        // for (auto &&cube : cubes) {
        //     cube->applyShape(cube_shader);
        //     cube->drawShape();
        // }

        sphere_shader.use();
        sphere_shader.setVec3(Shader::LIGHT_POS, cube_light.getPos());
        sphere_shader.setMat4(Shader::VIEW_MAT, camera.getViewMatrix());
        sphere_shader.setVec3(Shader::VIEW_POS, camera.getPosition());
        cube_light.applyLight(sphere_shader);
        sphere.applyShape(sphere_shader);
        sphere.drawShape();

        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }

    cube_template.free_VAO_VBO();
    cube_light.free_VAO_VBO();
    glfwTerminate();
    return 0;
}
