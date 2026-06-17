#include "GlfwContext.h"
#include "Match.h"
#include "Physics.h"
#include "GameTime.h"
#include "Input.h"
#include "Fighter.h"
#include "FighterController.h"
#include "FighterCommand.h"
#include "CharacterData.h"
#include "QuadMesh.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "Window.h"
#include "CombatSystem.h"
#include "FighterStateMachine.h"

#include <glad/glad.h>

#include <filesystem>
#include <iostream>

namespace
{
constexpr int kWindowWidth = 800;
constexpr int kWindowHeight = 600;

constexpr char kWindowTitle[] =
    "Street Fighter 2D";

std::filesystem::path getExecutableDirectory(
    char* executablePath)
{
    return std::filesystem::absolute(
        executablePath).parent_path();
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

    glClear(
        GL_COLOR_BUFFER_BIT);

    renderer.draw(
        match.fighter1().physics.transform,
        match.fighter1().facing,
        *match.fighter1().character->idleTexture);

    renderer.draw(
        match.fighter2().physics.transform,
        match.fighter2().facing,
        *match.fighter2().character->idleTexture);
}
}

int main(
    int,
    char* argv[])
{
    std::cout << "PROGRAM START\n";

    GlfwContext glfw;

    if (!glfw.isValid())
    {
        std::cout << "GLFW FAILED\n";
        return 1;
    }

    std::cout << "GLFW OK\n";

    Window window(
        kWindowWidth,
        kWindowHeight,
        kWindowTitle);

    if (!window.isValid())
    {
        std::cout << "WINDOW FAILED\n";
        return 1;
    }

    std::cout << "WINDOW OK\n";

    Input::Initialize(
        window.glfwHandle());

    const std::filesystem::path executableDir =
        getExecutableDirectory(
            argv[0]);

    std::cout
        << "Executable directory:\n"
        << executableDir
        << "\n\n";

    Shader shader(
        executableDir / "triangle.vert",
        executableDir / "triangle.frag");

    Texture ryuTexture(
    executableDir / "Assets/Textures/ryu.png");

    Texture kenTexture(
    executableDir / "Assets/Textures/rye2.png");

    QuadMesh quad;

    if (!shader.isValid())
    {
        std::cout << "SHADER FAILED\n";
        return 1;
    }

    std::cout << "SHADER OK\n";

    if (!ryuTexture.isValid())
    {
        std::cout << "RYU TEXTURE FAILED\n";
        return 1;
    }

    std::cout << "RYU TEXTURE OK\n";

    if (!kenTexture.isValid())
    {
        std::cout << "KEN TEXTURE FAILED\n";
        return 1;
    }

    std::cout << "KEN TEXTURE OK\n";

    if (!quad.isValid())
    {
        std::cout << "QUAD FAILED\n";
        return 1;
    }

    std::cout << "QUAD OK\n";

    CharacterData ryu;
    ryu.idleTexture =
        &ryuTexture;

    CharacterData ken;
    ken.idleTexture =
        &kenTexture;

    Renderer renderer(
        shader,
        quad);

    Match match;

    match.fighter1().character =
        &ryu;

    match.fighter2().character =
        &ken;

    Physics physics;
    CombatSystem combat;
    FighterStateMachine stateMachine;
    GameTime gameTime;
    FighterController controller;

    std::cout << "ENTERING GAME LOOP\n";

    while (!window.shouldClose())
    {
        gameTime.update();

        window.processInput();

        Fighter& fighter1 =
            match.fighter1();

        Fighter& fighter2 =
            match.fighter2();

        FighterCommand cmd1 =
            controller.build(true);

        FighterCommand cmd2 =
            controller.build(false);

        physics.update(
            match,
            gameTime.deltaTime(),
            cmd1,
            cmd2);

        stateMachine.update(
            fighter1,
            cmd1);

        stateMachine.update(
            fighter2,
            cmd2);

        combat.update(
            match,
            stateMachine);

        renderFrame(
            renderer,
            match);

        window.swapBuffers();

        window.pollEvents();
    }

    return 0;
}