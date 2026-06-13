#include "GlfwContext.h"
#include "Match.h"
#include "Physics.h"
#include "GameTime.h"
#include "Input.h"
#include "Fighter.h"
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

constexpr char kWindowTitle[] = "Street Fighter 2D";

constexpr char kVertexShaderPath[] = "triangle.vert";
constexpr char kFragmentShaderPath[] = "triangle.frag";

std::filesystem::path getExecutableDirectory(char* executablePath)
{
    return std::filesystem::absolute(executablePath).parent_path();
}

void renderFrame(
    const Renderer& renderer,
    const Match& match)
{
    glClearColor(
        0.08f,
        0.10f,
        0.12f,
        1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    renderer.draw(
        match.fighter1().transform());

    renderer.draw(
        match.fighter2().transform());
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

    Match match;

    Physics physics;

    GameTime gameTime;

    while (!window.shouldClose())
    {
        gameTime.update();

        window.processInput();

        Fighter& fighter1 =
            match.fighter1();

        Fighter& fighter2 =
            match.fighter2();

        //
        // Reset movimiento horizontal
        //
        fighter1.velocityX() = 0.0f;
        fighter2.velocityX() = 0.0f;

        //
        // Fighter 1
        // A D W
        //
        if (Input::IsKeyDown(Key::A))
        {
            fighter1.velocityX() =
                -Fighter::MoveSpeed;
        }

        if (Input::IsKeyDown(Key::D))
        {
            fighter1.velocityX() =
                Fighter::MoveSpeed;
        }

        if (Input::IsKeyDown(Key::W) &&
            fighter1.grounded())
        {
            fighter1.velocityY() =
                Fighter::JumpSpeed;
        }

        //
        // Fighter 2
        // J L I
        //
        if (Input::IsKeyDown(Key::J))
        {
            fighter2.velocityX() =
                -Fighter::MoveSpeed;
        }

        if (Input::IsKeyDown(Key::L))
        {
            fighter2.velocityX() =
                Fighter::MoveSpeed;
        }

        if (Input::IsKeyDown(Key::I) &&
            fighter2.grounded())
        {
            fighter2.velocityY() =
                Fighter::JumpSpeed;
        }

        physics.update(
            match,
            gameTime.deltaTime());

        fighter1.updateState();
        fighter2.updateState();

        renderFrame(
            renderer,
            match);

        window.swapBuffers();

        window.pollEvents();
    }

    return 0;
}