cmake_minimum_required(VERSION 3.16)

project(StreetFight2D LANGUAGES C CXX)

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

add_executable(StreetFight2D

    main.cpp

    # Platform
    src/Platform/GlfwContext.cpp
    src/Platform/Window.cpp

    # Graphics
    src/Graphics/Shader.cpp
    src/Graphics/Renderer.cpp
    src/Graphics/QuadMesh.cpp
    src/Graphics/TriangleMesh.cpp
    src/Graphics/Texture.cpp
    src/Graphics/StbImage.cpp

    # Core
    src/Core/GameTime.cpp
    src/Core/Input.cpp
    src/Core/Match.cpp
    src/Core/Stage.cpp

    # Fighter
    src/Fighter/Fighter.cpp
    src/Fighter/FighterController.cpp
    src/Fighter/CharacterPresets.cpp

    # Animation
    src/Animation/AssetManager.cpp

    # Systems
    src/Systems/Physics.cpp
    src/Systems/CombatSystem.cpp
    src/Systems/FighterStateMachine.cpp
    src/Systems/AnimationSystem.cpp
    src/Systems/AnimationPlayer.cpp

    # Pushbox (si existe)
    src/Systems/FighterPushboxSystem.cpp
)

# =========================================================
# INCLUDE DIRECTORIES
# =========================================================

target_include_directories(
    StreetFight2D PRIVATE

    src

    src/Core
    src/Fighter
    src/Graphics
    src/Platform
    src/Systems
    src/Animation

    externals/glad/include
    externals/glfw-3.4/include
    externals/glm
    externals/stb
)

# =========================================================
# DEFINITIONS
# =========================================================

target_compile_definitions(
    StreetFight2D PRIVATE
    GLFW_INCLUDE_NONE
)

# =========================================================
# LINK LIBRARIES
# =========================================================

target_link_libraries(
    StreetFight2D PRIVATE
    glfw
    glad
    opengl32
)

# =========================================================
# COPY ASSETS
# =========================================================

add_custom_command(
    TARGET StreetFight2D
    POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/Assets
        $<TARGET_FILE_DIR:StreetFight2D>/Assets
)