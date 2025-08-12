#include <window.h>
#include <camera.h>
#include <shader.h>
#include <cube.h>
#include <input.h>

int main() {
    Window window(1280, 1000, std::tuple(0, 0, 0, 0.8));
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    Input input(&camera, &window);

    Shader shader("../../resources/shaders/vertex_shader.glsl", "../../resources/shaders/fragment_shader.glsl");
    Cube cube{};

    char background[] = "../../resources/textures/yellow.png";
    char frame[] = "../../resources/textures/frame4.png";
    shader.loadTexture(background);
    shader.loadTexture(frame);
    shader.setProjectionMatrix(cube.getProjectionMatrix());

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 viewMatrix = glm::mat4(1.0f);

    glm::mat4 scaleDown = glm::mat4(1.0f);
    float scale_factor = -0.1;
    scaleDown = glm::scale(scaleDown, glm::vec3(scale_factor, scale_factor, scale_factor));
    shader.setScaleMatrix(scaleDown);

    glm::mat4 translate = glm::mat4(1.0f);
    translate = glm::translate(translate, glm::vec3(-2.0f, -2.0f, 1.0f));

    while (!glfwWindowShouldClose(window.getWindow())) {
        input.processInput();

        window.clearScreen();

        shader.use();

        shader.setViewMatrix(camera.getViewMatrix());

        shader.setTranslationMatrix(glm::mat4(1.0f));
        modelMatrix =
            glm::rotate(cube.getModelMatrix(), (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        shader.setModelMatrix(modelMatrix);
        cube.drawShape();

        shader.setTranslationMatrix(translate);
        shader.setModelMatrix(glm::mat4(1.0f));
        cube.drawShape();

        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }

    cube.destruct();
    glfwTerminate();
    return 0;
}
