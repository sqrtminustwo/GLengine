cmake_minimum_required(VERSION 3.20)
project(GLengine LANGUAGES C CXX)

# C++ settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Packages
find_package(glm CONFIG REQUIRED)
find_package(Freetype REQUIRED)
find_package(ftxui REQUIRED)

# Collect source files
file(GLOB_RECURSE CPP_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/shape/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stats/*.cpp
)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/engine/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/engine/shape/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/engine/shape/cube/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/engine/shape/cube/cube_colored/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/engine/shape/cube/cube_textured/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/stats/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)
set(SOURCES ${CPP_SOURCES} ${C_SOURCES})

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE
    PROJECT_DIR="${CMAKE_SOURCE_DIR}"
)

# Include directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/engine
        ${CMAKE_CURRENT_SOURCE_DIR}/include/engine/shape
        ${CMAKE_CURRENT_SOURCE_DIR}/include/engine/shape/cube
        ${CMAKE_CURRENT_SOURCE_DIR}/include/engine/shape/cube/cube_colored
        ${CMAKE_CURRENT_SOURCE_DIR}/include/engine/shape/cube/cube_textured
        ${CMAKE_CURRENT_SOURCE_DIR}/include/stats
        ${CMAKE_CURRENT_SOURCE_DIR}/external/include
        ${FREETYPE_INCLUDE_DIRS} # Include FreeType
)

# Add glm
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

# Add glad
add_library(glad STATIC ${CMAKE_CURRENT_SOURCE_DIR}/external/glad.c)

# Add ftxui
find_package(ftxui REQUIRED)
target_link_libraries(${PROJECT_NAME}
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)

if (WIN32)
    # GLFW
    add_library(glfw STATIC IMPORTED GLOBAL)
    set_target_properties(glfw PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/glfw3.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/external/include"
    )

    target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_STATIC)

    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            glad
            glfw
            ${FREETYPE_LIBRARIES} # Link FreeType
            opengl32
            gdi32
            user32
            shell32
            advapi32
            kernel32
    )
else()
    # GLFW
    add_library(glfw STATIC IMPORTED GLOBAL)
    set_target_properties(glfw PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libglfw3.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/external/include"
    )

    target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_STATIC)

    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            glad
            glfw
            ${FREETYPE_LIBRARIES} # Link FreeType
            GL
            X11
            pthread
            dl
            m
    )
endif()

# Compiler warnings
# if (MSVC)
#     target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
# else()
#     target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
# endif()

# Link Time Optimization
include(CheckIPOSupported)
check_ipo_supported(RESULT result)
if(result)
    set_target_properties(${PROJECT_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()
