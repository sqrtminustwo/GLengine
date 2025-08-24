#include <window.h>
#include <camera.h>
#include <cube.h>
#include <input.h>
#include <shader.h>
#include <stats.h>
#include <plot.h>

using triplet = std::tuple<float, float, float>;
using cube_ptr = std::unique_ptr<Cube>;

void genAndAddCubes(Cube cube_template, std::vector<cube_ptr> &cubes, std::vector<triplet> coords) {
    for (auto coord : coords) {
        std::unique_ptr<Cube> cube(new Cube{cube_template});
        auto [x, y, z] = coord;
        cube->setPos(x, y, z);
        cubes.push_back(std::move(cube));
    }
}

int main() {
    Window window(1280, 1000, std::tuple(0, 0, 0, 0.7));
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    Input input(&camera, &window);

    Shader shape_shader(
        PROJECT_DIR "/resources/shaders/shape/vertex_shader.glsl",
        PROJECT_DIR "/resources/shaders/shape/fragment_shader.glsl"
    );

    Cube cube_template{};
    std::vector<cube_ptr> cubes;
    std::vector<triplet> triplet{};

    int size = 10;

    for (float i = 0; i <= size; i++) {
        triplet.clear();
        triplet.insert(triplet.end(), {{-i, 0.0f, 0.0f}, {-i, -size, 0.0f}, {-i, 0.0f, -size}, {-i, -size, -size}});
        genAndAddCubes(cube_template, cubes, triplet);

        triplet.clear();
        triplet.insert(triplet.end(), {{0.0f, -i, 0.0f}, {-size, -i, 0.0f}, {0.0f, -i, -size}, {-size, -i, -size}});
        genAndAddCubes(cube_template, cubes, triplet);

        triplet.clear();
        triplet.insert(triplet.end(), {{0.0f, 0.0f, -i}, {0.0f, -size, -i}, {-size, 0.0f, -i}, {-size, -size, -i}});
        genAndAddCubes(cube_template, cubes, triplet);
    }

    char background[] = PROJECT_DIR "/resources/textures/yellow.png";
    char frame[] = PROJECT_DIR "/resources/textures/frame4.png";
    shape_shader.loadTexture(background);
    shape_shader.loadTexture(frame);
    shape_shader.setProjectionMatrix(cubes.at(0)->getProjectionMatrix());

    glm::mat4 scaleDown = glm::mat4(1.0f);
    float scale_factor = -0.1;
    scaleDown = glm::scale(scaleDown, glm::vec3(scale_factor, scale_factor, scale_factor));
    shape_shader.setScaleMatrix(scaleDown);

    Stats stats{};
    stats.start(); // End is defined in class destructor

    while (!glfwWindowShouldClose(window.getWindow())) {
        stats.updateFps();

        input.processInput();

        window.clearScreen();

        shape_shader.use();

        shape_shader.setViewMatrix(camera.getViewMatrix());

        for (auto &&cube : cubes) {
            shape_shader.setModelMatrix(cube->getModelMatrix());
            shape_shader.setProjectionMatrix(cube->getProjectionMatrix());
            shape_shader.setTranslationMatrix(cube->getTranslationMatrix());
            cube->drawShape();
        }

        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }

    for (auto &&cube : cubes) cube->free_VAO_VBO();
    glfwTerminate();
    return 0;
}
