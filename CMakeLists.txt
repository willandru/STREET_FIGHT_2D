cmake_minimum_required(VERSION 3.16)

project(Engine2D LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =========================================================
# GLFW
# =========================================================
add_subdirectory(externals/glfw-3.4)

# =========================================================
# GLAD
# =========================================================
add_library(glad
    externals/glad/src/glad.c
)

target_include_directories(glad PUBLIC
    externals/glad/include
)

# =========================================================
# EXECUTABLE
# =========================================================
add_executable(Engine2D
    main.cpp

    src/GlfwContext.cpp
    src/Window.cpp

    src/Shader.cpp
    src/QuadMesh.cpp
    src/Renderer.cpp

    src/Platform.cpp
    src/Player.cpp
    src/Level.cpp

    src/Physics.cpp
    src/GameTime.cpp
    src/Input.cpp
)

# =========================================================
# INCLUDE DIRS
# =========================================================
target_include_directories(Engine2D PRIVATE
    src

    externals/glad/include
    externals/glfw-3.4/include

    externals/glm
)

target_compile_definitions(
    Engine2D PRIVATE
    GLFW_INCLUDE_NONE
)

# =========================================================
# LINK
# =========================================================
target_link_libraries(
    Engine2D PRIVATE
    glfw
    glad
    opengl32
)

# =========================================================
# COPY SHADERS
# =========================================================
add_custom_command(
    TARGET Engine2D POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/triangle.vert
        ${CMAKE_SOURCE_DIR}/triangle.frag
        $<TARGET_FILE_DIR:Engine2D>
)