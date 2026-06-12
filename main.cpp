#include "GlfwContext.h"
#include "Level.h"
#include "Physics.h"
#include "GameTime.h"
#include "Input.h"
#include "Player.h"
#include "QuadMesh.h"
#include "Renderer.h"
#include "Shader.h"
#include "Window.h"

#include <glad/glad.h>

#include <filesystem>

namespace
{
constexpr int kWindowWidth = 800;
constexpr int kWindowHeight = 600;

constexpr char kWindowTitle[] = "2D Engine";

constexpr char kVertexShaderPath[] = "triangle.vert";
constexpr char kFragmentShaderPath[] = "triangle.frag";

std::filesystem::path getExecutableDirectory(char* executablePath)
{
    return std::filesystem::absolute(executablePath).parent_path();
}

void renderFrame(
    const Renderer& renderer,
    const Level& level)
{
    glClearColor(
        0.08f,
        0.10f,
        0.12f,
        1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    for (const auto& platform : level.platforms())
    {
        renderer.draw(
            platform.transform());
    }

    renderer.draw(
        level.player().transform());
}
}

int main(int, char* argv[])
{
    GlfwContext glfw;

    if (!glfw.isValid())
    {
        return 1;
    }

    Window window(
        kWindowWidth,
        kWindowHeight,
        kWindowTitle);

    if (!window.isValid())
    {
        return 1;
    }

    Input::Initialize(
        window.glfwHandle());

    const std::filesystem::path shaderDirectory =
        getExecutableDirectory(argv[0]);

    Shader shader(
        shaderDirectory / kVertexShaderPath,
        shaderDirectory / kFragmentShaderPath);

    QuadMesh quad;

    if (!shader.isValid() ||
        !quad.isValid())
    {
        return 1;
    }

    Renderer renderer(
        shader,
        quad);

    Level level;

    Physics physics;

    GameTime gameTime;

    while (!window.shouldClose())
    {
        gameTime.update();

        window.processInput();

        Player& player =
            level.player();

        player.velocityX() = 0.0f;

        if (Input::IsKeyDown(Key::A))
        {
            player.velocityX() =
                -Player::MoveSpeed;
        }

        if (Input::IsKeyDown(Key::D))
        {
            player.velocityX() =
                Player::MoveSpeed;
        }

        if (Input::IsKeyDown(Key::W) &&
            player.grounded())
        {
            player.velocityY() =
                Player::JumpSpeed;
        }

        physics.update(
            level,
            gameTime.deltaTime());

        renderFrame(
            renderer,
            level);

        window.swapBuffers();

        window.pollEvents();
    }

    return 0;
}