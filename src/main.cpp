#include <window.h>
#include <camera.h>
#include <cube.h>
#include <input.h>
#include <shader.h>
#include <frame_rate.h>
#include <text.h>

int main() {
    Window window(1280, 1000, std::tuple(0, 0, 0, 0.7));
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    Input input(&camera, &window);

    Shader shape_shader(
        "../../resources/shaders/shape/vertex_shader.glsl",
        "../../resources/shaders/shape/fragment_shader.glsl"
    );

    Shader text_shader(
        "../../resources/shaders/text/vertex_shader.glsl",
        "../../resources/shaders/text/fragment_shader.glsl"
    );

    std::vector<Cube *> cubes;

    Cube cube1{};
    cubes.push_back(&cube1);

    Cube cube2{cube1};
    glm::mat4 translate = glm::mat4(1.0f);
    translate = glm::translate(translate, glm::vec3(-2.0f, -2.0f, 1.0f));
    cube2.setTranslationMatrix(translate);
    cubes.push_back(&cube2);

    char background[] = "../../resources/textures/yellow.png";
    char frame[] = "../../resources/textures/frame4.png";
    shape_shader.loadTexture(background);
    shape_shader.loadTexture(frame);
    shape_shader.setProjectionMatrix(cube1.getProjectionMatrix());

    glm::mat4 scaleDown = glm::mat4(1.0f);
    float scale_factor = -0.1;
    scaleDown = glm::scale(scaleDown, glm::vec3(scale_factor, scale_factor, scale_factor));
    shape_shader.setScaleMatrix(scaleDown);

    FrameRate frameRate{};
    Text text{text_shader};

    while (!glfwWindowShouldClose(window.getWindow())) {
        frameRate.stat();
        input.processInput();

        window.clearScreen();

        shape_shader.use();

        cube1.setModelMatrix(
            glm::rotate(cube1.getModelMatrix(), (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f))
        );
        shape_shader.setViewMatrix(camera.getViewMatrix());

        for (Cube *cube : cubes) {
            shape_shader.setModelMatrix(cube->getModelMatrix());
            shape_shader.setProjectionMatrix(cube->getProjectionMatrix());
            shape_shader.setTranslationMatrix(cube->getTranslationMatrix());
            cube->drawShape();
        }

        text.renderText(text_shader, "Test", 25.0f, 25.0f, 1.0f, glm::vec3(0.3, 0.7f, 0.9f));

        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }

    for (Cube *cube : cubes) cube->destruct();
    glfwTerminate();
    return 0;
}
