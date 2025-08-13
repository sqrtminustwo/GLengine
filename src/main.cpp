#include <window.h>
#include <camera.h>
#include <shader.h>
#include <cube.h>
#include <input.h>
#include <frame_rate.h>

int main() {
    Window window(1280, 1000, std::tuple(0, 0, 0, 0.7));
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    Input input(&camera, &window);

    Shader shader("../../resources/shaders/vertex_shader.glsl", "../../resources/shaders/fragment_shader.glsl");

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
    shader.loadTexture(background);
    shader.loadTexture(frame);
    shader.setProjectionMatrix(cube1.getProjectionMatrix());

    glm::mat4 scaleDown = glm::mat4(1.0f);
    float scale_factor = -0.1;
    scaleDown = glm::scale(scaleDown, glm::vec3(scale_factor, scale_factor, scale_factor));
    shader.setScaleMatrix(scaleDown);

    FrameRate frameRate;

    while (!glfwWindowShouldClose(window.getWindow())) {
        frameRate.stat();
        input.processInput();

        window.clearScreen();

        shader.use();

        cube1.setModelMatrix(
            glm::rotate(cube1.getModelMatrix(), (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f))
        );
        shader.setViewMatrix(camera.getViewMatrix());

        for (Cube *cube : cubes) {
            shader.setModelMatrix(cube->getModelMatrix());
            shader.setProjectionMatrix(cube->getProjectionMatrix());
            shader.setTranslationMatrix(cube->getTranslationMatrix());
            cube->drawShape();
        }

        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }

    for (Cube *cube : cubes) cube->destruct();
    glfwTerminate();
    return 0;
}
