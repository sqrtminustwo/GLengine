#include "light.h"
#include <glad.h>
#include <GLFW/glfw3.h>
#include <sphere_textured.h>
#include <cube_textured.h>
#include <square.h>
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
        PROJECT_DIR "/resources/shaders/shape/textured/vertex_shader.glsl",
        PROJECT_DIR "/resources/shaders/shape/textured/fragment_shader.glsl"
    );
    Shader sphere_light_shader(
        PROJECT_DIR "/resources/shaders/shape/lighting/textured/vertex_shader.glsl",
        PROJECT_DIR "/resources/shaders/shape/lighting/textured/fragment_shader.glsl"
    );
    Shader cube_shader(
        PROJECT_DIR "/resources/shaders/shape/textured/vertex_shader.glsl",
        PROJECT_DIR "/resources/shaders/shape/textured/fragment_shader.glsl"
    );
    Shader square_shader(
        PROJECT_DIR "/resources/shaders/shape/textured/vertex_shader.glsl",
        PROJECT_DIR "/resources/shaders/shape/textured/fragment_shader.glsl"
    );

    constexpr float scaleFactor = 0.1f;

    SphereTextured sphere_light;
    sphere_light.setScale(scaleFactor);
    sphere_light.setDiffuse(PROJECT_DIR "/resources/textures/moon.png");

    SphereTextured sphere_middle{sphere_light};
    sphere_middle.setScale(0.5f);
    // sphere_middle.setLinesOnly(true);
    sphere_middle.setDiffuse(PROJECT_DIR "/resources/textures/earth.png");

    cube_type cube_template{};
    cube_template.setScale(scaleFactor);
    cube_template.setDiffuse(PROJECT_DIR "/resources/textures/container.png");
    cube_template.setSpecular(PROJECT_DIR "/resources/textures/container_specular.png");
    // cube_template.setEmission(PROJECT_DIR "/resources/textures/container_emission.jpg");
    cube_template.setShininess(1.0f);
    std::vector<cube_ptr> cubes;

    Light light_source{};
    light_source.setAmbient(0.2f, 0.2f, 0.2f);
    light_source.setDiffuse(0.5f, 0.5f, 0.5f);
    light_source.setSpecular(1.0f, 1.0f, 1.0f);

    Square square;
    square.setScale(scaleFactor);
    square.setRotate(90.0f, Shape::X);
    square.setDiffuse(PROJECT_DIR "/resources/textures/grass.jpg");

    Square square2{square};
    square2.setPos(0.0f, -1.0f, 0.0f);

    constexpr auto size = 10;
    constexpr auto middle = size / 2;
    triplet left_bottom_corner{middle, middle, middle};
    constexpr auto radius = 10;

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

        sphere_light_shader.setMat4(Shader::VIEW_MAT, camera.getViewMatrix());
        auto time = glfwGetTime();
        auto x = radius * std::cos(time);
        auto y = radius * std::sin(time);
        auto z = 0;
        sphere_light.setPos(x, y, y);
        sphere_light.applyShape(sphere_light_shader);
        sphere_light.drawShape();

        // cube_shader.setVec3(Shader::LIGHT_POS, sphere_light.getPos());
        // cube_shader.setMat4(Shader::VIEW_MAT, camera.getViewMatrix());
        // cube_shader.setVec3(Shader::VIEW_POS, camera.getPosition());
        //
        // light_source.applyLight(cube_shader);
        // for (auto &&cube : cubes) {
        //     cube->applyShape(cube_shader);
        //     cube->drawShape();
        // }
        //
        // sphere_shader.setMat4(Shader::VIEW_MAT, camera.getViewMatrix());
        // sphere_shader.setVec3(Shader::LIGHT_POS, sphere_light.getPos());
        // sphere_shader.setMat4(Shader::VIEW_MAT, camera.getViewMatrix());
        // sphere_shader.setVec3(Shader::VIEW_POS, camera.getPosition());
        // light_source.applyLight(sphere_shader);
        // sphere_middle.applyShape(sphere_shader);
        // sphere_middle.drawShape();

        square_shader.setMat4(Shader::VIEW_MAT, camera.getViewMatrix());
        square_shader.setVec3(Shader::LIGHT_POS, sphere_light.getPos());
        square_shader.setMat4(Shader::VIEW_MAT, camera.getViewMatrix());
        square_shader.setVec3(Shader::VIEW_POS, camera.getPosition());
        light_source.applyLight(square_shader);
        square.applyShape(square_shader);
        square.drawShape();

        square2.applyShape(square_shader);
        square2.drawShape();

        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }

    cube_template.free_VAO_VBO();
    glfwTerminate();
    return 0;
}
