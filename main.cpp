#include "GlfwContext.h"
#include "Match.h"
#include "Physics.h"
#include "GameTime.h"
#include "Input.h"
#include "Fighter.h"
#include "FighterController.h"
#include "FighterCommand.h"
#include "QuadMesh.h"
#include "Renderer.h"
#include "Shader.h"
#include "Window.h"
#include "CombatSystem.h"
#include "FighterStateMachine.h"

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
    glClearColor(0.08f, 0.10f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderer.draw(match.fighter1().transform());
    renderer.draw(match.fighter2().transform());
}
}

int main(int, char* argv[])
{
    GlfwContext glfw;

    if (!glfw.isValid())
        return 1;

    Window window(
        kWindowWidth,
        kWindowHeight,
        kWindowTitle);

    if (!window.isValid())
        return 1;

    Input::Initialize(window.glfwHandle());

    const std::filesystem::path shaderDirectory =
        getExecutableDirectory(argv[0]);

    Shader shader(
        shaderDirectory / kVertexShaderPath,
        shaderDirectory / kFragmentShaderPath);

    QuadMesh quad;

    if (!shader.isValid() || !quad.isValid())
        return 1;

    Renderer renderer(shader, quad);

    Match match;
    Physics physics;
    CombatSystem combat;
    FighterStateMachine stateMachine;
    GameTime gameTime;
    FighterController controller;

    while (!window.shouldClose())
    {
        gameTime.update();
        window.processInput();

        Fighter& fighter1 = match.fighter1();
        Fighter& fighter2 = match.fighter2();

        // =========================
        // INPUT → COMMAND
        // =========================

        FighterCommand cmd1 = controller.build(true);
        FighterCommand cmd2 = controller.build(false);

        // =========================
        // STATE MACHINE (INPUT LOGIC)
        // =========================

        stateMachine.applyCommand(fighter1, cmd1);
        stateMachine.applyCommand(fighter2, cmd2);

        // =========================
        // PHYSICS (MOVEMENT ONLY)
        // =========================

        physics.update(
            match,
            gameTime.deltaTime(),
            cmd1,
            cmd2);

        // =========================
        // STATE UPDATE (POST PHYSICS)
        // =========================

        stateMachine.updateState(fighter1);
        stateMachine.updateState(fighter2);

        // =========================
        // COMBAT RESOLUTION
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