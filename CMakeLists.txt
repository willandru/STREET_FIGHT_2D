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
add_library(glad externals/glad/src/glad.c)
target_include_directories(glad PUBLIC externals/glad/include)

# =========================================================
# EXECUTABLE
# =========================================================
add_executable(StreetFight2D
    main.cpp

    src/Platform/GlfwContext.cpp
    src/Platform/Window.cpp

    src/Graphics/Shader.cpp
    src/Graphics/Renderer.cpp
    src/Graphics/QuadMesh.cpp
    src/Graphics/TriangleMesh.cpp
    src/Graphics/Texture.cpp
    src/Graphics/StbImage.cpp

    src/Core/GameTime.cpp
    src/Core/Input.cpp
    src/Core/Match.cpp
    src/Core/Stage.cpp

    src/Fighter/Fighter.cpp
    src/Fighter/FighterController.cpp
    src/Fighter/CharacterPresets.cpp

    src/Animation/AssetManager.cpp

    src/Systems/Physics.cpp
    src/Systems/CombatSystem.cpp
    src/Systems/FighterStateMachine.cpp
    src/Systems/AnimationSystem.cpp
    src/Systems/AnimationPlayer.cpp
)

target_include_directories(StreetFight2D PRIVATE
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

target_compile_definitions(StreetFight2D PRIVATE GLFW_INCLUDE_NONE)

target_link_libraries(StreetFight2D PRIVATE glfw glad opengl32)

# =========================================================
# COPY SHADERS (CRÍTICO)
# =========================================================
add_custom_command(
    TARGET StreetFight2D POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:StreetFight2D>/Assets

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/Assets
        $<TARGET_FILE_DIR:StreetFight2D>/Assets
)