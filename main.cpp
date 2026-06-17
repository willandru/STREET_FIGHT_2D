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
#include "CharacterPresets.h"
#include "AnimationSystem.h"

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
    return std::filesystem::absolute(executablePath).parent_path();
}

void renderFrame(
    const Renderer& renderer,
    const Match& match)
{
    glClearColor(0.08f, 0.10f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    const Fighter& f1 = match.fighter1();
    const Fighter& f2 = match.fighter2();

    auto drawFighter =
        [&](const Fighter& f)
        {
            if (!f.currentAnimation ||
                f.currentAnimation->frames.empty())
            {
                return;
            }

            const Texture* tex =
                f.currentAnimation
                    ->frames[f.currentFrame]
                    .texture;

            if (tex)
            {
                renderer.draw(
                    f.physics.transform,
                    f.facing,
                    *tex);
            }
        };

    drawFighter(f1);
    drawFighter(f2);
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

    Input::Initialize(window.glfwHandle());

    const std::filesystem::path executableDir =
        getExecutableDirectory(argv[0]);

    Shader shader(
        executableDir / "triangle.vert",
        executableDir / "triangle.frag");

    QuadMesh quad;

    if (!shader.isValid() || !quad.isValid())
    {
        return 1;
    }

    // =========================
    // LOAD TEXTURES (TEMPORAL - FASE ACTUAL)
    // =========================

    Texture ryu_idle_1(executableDir / "Assets/Textures/ryu/idle_ryu/ryu_idle_1.png");
    Texture ryu_idle_2(executableDir / "Assets/Textures/ryu/idle_ryu/ryu_idle_2.png");
    Texture ryu_idle_3(executableDir / "Assets/Textures/ryu/idle_ryu/ryu_idle_3.png");
    Texture ryu_idle_4(executableDir / "Assets/Textures/ryu/idle_ryu/ryu_idle_4.png");

    Texture ken_idle_1(executableDir / "Assets/Textures/ryu/idle_ryu/ryu_idle_1.png");
    Texture ken_idle_2(executableDir / "Assets/Textures/ryu/idle_ryu/ryu_idle_2.png");
    Texture ken_idle_3(executableDir / "Assets/Textures/ryu/idle_ryu/ryu_idle_3.png");
    Texture ken_idle_4(executableDir / "Assets/Textures/ryu/idle_ryu/ryu_idle_4.png");

    if (!ryu_idle_1.isValid() || !ryu_idle_4.isValid())
    {
        return 1;
    }

    if (!ken_idle_1.isValid() || !ken_idle_4.isValid())
    {
        return 1;
    }

    // =========================
    // CHARACTER CREATION (NEW SYSTEM)
    // =========================

    CharacterData ryu =
        Characters::createRyu(
            ryu_idle_1,
            ryu_idle_2,
            ryu_idle_3,
            ryu_idle_4);

    CharacterData ken =
        Characters::createKen(
            ken_idle_1,
            ken_idle_2,
            ken_idle_3,
            ken_idle_4);

    Renderer renderer(shader, quad);

    Match match;

    match.fighter1().character = &ryu;
    match.fighter2().character = &ken;

    Physics physics;
    CombatSystem combat;
    FighterStateMachine stateMachine;
    AnimationSystem animationSystem;
    GameTime gameTime;
    FighterController controller;

    while (!window.shouldClose())
    {
        gameTime.update();
        window.processInput();

        Fighter& fighter1 = match.fighter1();
        Fighter& fighter2 = match.fighter2();

        FighterCommand cmd1 = controller.build(true);
        FighterCommand cmd2 = controller.build(false);

        // =========================
        // PHYSICS
        // =========================
        physics.update(
            match,
            gameTime.deltaTime(),
            cmd1,
            cmd2);

        // =========================
        // STATE MACHINE
        // =========================
        stateMachine.update(fighter1, cmd1);
        stateMachine.update(fighter2, cmd2);

        // =========================
        // ANIMATION SYSTEM
        // =========================
        animationSystem.update(fighter1, gameTime.deltaTime());
        animationSystem.update(fighter2, gameTime.deltaTime());

        // =========================
        // COMBAT
        // =========================
        combat.update(match, stateMachine);

        // =========================
        // RENDER
        // =========================
        renderFrame(renderer, match);

        window.swapBuffers();
        window.pollEvents();
    }

    return 0;
}