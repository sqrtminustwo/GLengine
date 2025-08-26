#include <cube_colored.h>
#include <window.h>
#include <camera.h>
#include <cube_textured.h>
#include <input.h>
#include <shader.h>
#include <stats.h>
#include <plot.h>

using triplet = std::tuple<float, float, float>;
using cube_type = CubeColored;
using cube_ptr = std::unique_ptr<cube_type>;

void genAndAddCubes(
    cube_type cube_template, std::vector<cube_ptr> &cubes, std::vector<triplet> &&coords, triplet left_bottom_corner
) {
    for (auto coord : coords) {
        std::unique_ptr<cube_type> cube(new cube_type{cube_template});
        auto [base_x, base_y, base_z] = left_bottom_corner;
        auto [x, y, z] = coord;
        cube->setPos(base_x + x, base_y + y, base_z + z);
        cubes.push_back(std::move(cube));
    }
}

void applyAndDrawShape(CubeColored cube, Shader shader, bool colored = true) {
    shader.setModelMatrix(cube.getModelMatrix());
    shader.setProjectionMatrix(cube.getProjectionMatrix());
    shader.setTranslationMatrix(cube.getTranslationMatrix());
    if (colored) shader.setObjectColor(cube.getColor());
    cube.drawShape();
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

    cube_type cube_template{};
    cube_template.setColor(1.0f, 0.5f, 0.3f);
    std::vector<cube_ptr> cubes;

    // Single cube for light testing
    // genAndAddCubes(cube_template, cubes, {{0.0f, 0.0f, 0.0f}});

    CubeColored cube_light{};
    // Normal
    // For light testing
    // float dist = -2.0f;
    cube_light.setColor(1.0f, 1.0f, 1.0f);
    constexpr auto size = 10;
    constexpr auto middle = size / 2;
    triplet left_bottom_corner{middle, middle, middle};

    constexpr auto radius = 10;
    constexpr triplet middle_point{0, 0, 0};
    cube_light.setPos(-radius, -radius, 0);
    // 1) Make (0, 0, 0) centere of big cube
    // 1) Make cube move from [radius, -radius] with constant Y and Z
    // 2) Calculate Y using circle function and make it non static (Z stays static, cube moves in 2D)

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

    // use() SHOULD BE ALWAYS CALLED BEFORE SETTING UNIFORM (otherwise how would it know what uniform to set if no
    // shader is being used), use() is called in loadTexture() and all setMatrix()
    // char background[] = PROJECT_DIR "/resources/textures/yellow.png";
    // char frame[] = PROJECT_DIR "/resources/textures/frame4.png";
    // shape_shader.loadTexture(background);
    // shape_shader.loadTexture(frame);
    shape_shader.setProjectionMatrix(cube_template.getProjectionMatrix());

    glm::mat4 scaleDown{1.0f};
    auto scale_factor = -0.1;
    scaleDown = glm::scale(scaleDown, glm::vec3(scale_factor, scale_factor, scale_factor));
    shape_shader.setScaleMatrix(scaleDown);

    lighting_shader.setProjectionMatrix(cube_light.getProjectionMatrix());
    lighting_shader.setScaleMatrix(scaleDown);
    // Stats stats{};
    // stats.start(); // End is defined in class destructor

    while (!glfwWindowShouldClose(window.getWindow())) {
        // stats.updateFps();

        input.processInput();

        window.clearScreen();

        lighting_shader.setViewMatrix(camera.getViewMatrix());

        auto time = glfwGetTime();
        // Parametric circle equation
        auto x = radius * std::cos(time);
        auto y = radius * std::sin(time);
        cube_light.setPos(x, y, 0);

        applyAndDrawShape(cube_light, lighting_shader, false);

        shape_shader.setLightPos(cube_light.getPos());
        shape_shader.setLightColor(cube_light.getColor());
        shape_shader.setViewMatrix(camera.getViewMatrix());
        shape_shader.setViewPos(camera.getPosition());
        for (auto &&cube : cubes) applyAndDrawShape(*cube, shape_shader);

        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }

    cube_template.free_VAO_VBO();
    cube_light.free_VAO_VBO();
    glfwTerminate();
    return 0;
}
