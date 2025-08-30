#include <cube_colored.h>
#include <iostream>
#include <window.h>
#include <camera.h>
#include <input.h>
#include <shader.h>
#include <stats.h>
#include <plot.h>

using triplet = std::tuple<float, float, float>;
using cube_type = CubeColored;
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

    Shader shape_shader(
        PROJECT_DIR "/resources/shaders/shape/colored/vertex_shader.glsl",
        PROJECT_DIR "/resources/shaders/shape/colored/fragment_shader.glsl"
    );
    Shader lighting_shader(
        PROJECT_DIR "/resources/shaders/lighting/vertex_shader.glsl",
        PROJECT_DIR "/resources/shaders/lighting/fragment_shader.glsl"
    );

    constexpr float scaleFactor = 0.1f;

    cube_type cube_template{};
    cube_template.setScale(scaleFactor);
    cube_template.setAmbient(1.0f, 0.5f, 0.31f);
    cube_template.setDiffuse(1.0f, 0.5f, 0.31f);
    cube_template.setSpecular(0.5f, 0.5f, 0.5f);
    cube_template.setShininess(32.0f);
    std::vector<cube_ptr> cubes;

    CubeColored cube_light{};
    cube_light.setScale(scaleFactor);
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

    // use() SHOULD BE ALWAYS CALLED BEFORE SETTING UNIFORM (otherwise how would it know what
    // uniform to set if no shader is being used), use() is called in loadTexture() and all
    // setMatrix() char background[] = PROJECT_DIR "/resources/textures/yellow.png"; char frame[] =
    // PROJECT_DIR "/resources/textures/frame4.png"; shape_shader.loadTexture(background);
    // shape_shader.loadTexture(frame);

    // Stats stats{};
    // stats.start(); // End is defined in class destructor

    while (!glfwWindowShouldClose(window.getWindow())) {
        // stats.updateFps();

        input.processInput();

        window.clearScreen();

        // lighting_shader.setViewMatrix(camera.getViewMatrix());
        lighting_shader.setMat4(Shader::VIEW_MAT, camera.getViewMatrix());

        auto time = glfwGetTime();
        auto x = radius * std::cos(time);
        auto y = radius * std::sin(time);
        auto z = 0;
        cube_light.setPos(x, y, y);
        cube_light.applyShape(lighting_shader);
        cube_light.drawShape();

        // shape_shader.setLightPos(cube_light.getPos());
        // shape_shader.setLightColor(cube_light.getColor());
        // shape_shader.setViewMatrix(camera.getViewMatrix());
        // shape_shader.setViewPos(camera.getPosition());
        shape_shader.setVec3(Shader::LIGHT_POS, cube_light.getPos());
        shape_shader.setVec3(Shader::LIGHT_COLOR, cube_light.getColor());
        shape_shader.setMat4(Shader::VIEW_MAT, camera.getViewMatrix());
        shape_shader.setVec3(Shader::VIEW_POS, camera.getPosition());

        for (auto &&cube : cubes) {
            cube->applyShape(shape_shader);
            cube->drawShape();
        }

        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }

    cube_template.free_VAO_VBO();
    cube_light.free_VAO_VBO();
    glfwTerminate();
    return 0;
}
