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

    const std::filesystem::path executableDir =
        getExecutableDirectory(
            argv[0]);

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
        return 1;
    }

    if (!ryuTexture.isValid())
    {
        return 1;
    }

    if (!kenTexture.isValid())
    {
        return 1;
    }

    if (!quad.isValid())
    {
        return 1;
    }

    CharacterData ryu;

    ryu.idleTexture =
        &ryuTexture;

    ryu.moveSpeed =
        3.0f;

    ryu.jumpSpeed =
        6.5f;

    CharacterData ken;

    ken.idleTexture =
        &kenTexture;

    ken.moveSpeed =
        3.2f;

    ken.jumpSpeed =
        7.0f;

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