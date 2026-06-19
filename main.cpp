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
#include "Window.h"
#include "CombatSystem.h"
#include "FighterStateMachine.h"
#include "CharacterPresets.h"
#include "AnimationSystem.h"
#include "AnimationComponent.h"
#include "AssetManager.h"
#include "FighterPushboxSystem.h"

#include <glad/glad.h>
#include <filesystem>

namespace
{
constexpr int kWindowWidth = 800;
constexpr int kWindowHeight = 600;
constexpr char kWindowTitle[] = "Street Fighter 2D";

std::filesystem::path getExecutableDirectory(char* executablePath)
{
    return std::filesystem::absolute(executablePath).parent_path();
}

void renderFrame(const Renderer& renderer, const Match& match)
{
    glClearColor(0.08f, 0.10f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    auto drawFighter = [&](const Fighter& f)
    {
        if (!f.animation) return;

        const Texture* tex = f.animation->getTexture();
        if (!tex) return;

        renderer.draw(f.physics.transform, f.facing, *tex);
    };

    drawFighter(match.fighter1());
    drawFighter(match.fighter2());
}
}

int main(int, char* argv[])
{
    GlfwContext glfw;
    if (!glfw.isValid()) return 1;

    Window window(kWindowWidth, kWindowHeight, kWindowTitle);
    if (!window.isValid()) return 1;

    Input::Initialize(window.glfwHandle());

    const auto executableDir = getExecutableDirectory(argv[0]);

    Shader shader(
        executableDir / "Assets/Shaders/triangle.vert",
        executableDir / "Assets/Shaders/triangle.frag"
    );

    QuadMesh quad;
    if (!shader.isValid() || !quad.isValid()) return 1;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    AssetManager assets;
    assets.loadAll((executableDir / "Assets/Textures").string());

    CharacterData ryu = Characters::createRyu(assets);
    CharacterData ken = Characters::createKen(assets);

    Renderer renderer(shader, quad);

    Match match;
    match.fighter1().character = &ryu;
    match.fighter2().character = &ken;

    // =========================
    // NEW ANIMATION COMPONENTS
    // =========================
    AnimationComponent anim1;
    AnimationComponent anim2;

    match.fighter1().animation = &anim1;
    match.fighter2().animation = &anim2;

    Physics physics;
    CombatSystem combat;
    FighterStateMachine stateMachine;
    AnimationSystem animationSystem;
    FighterPushboxSystem pushboxSystem;
    GameTime gameTime;
    FighterController controller;

    while (!window.shouldClose())
    {
        gameTime.update();
        window.processInput();

        float dt = gameTime.deltaTime();
        if (dt > 0.033f) dt = 0.033f;

        Fighter& f1 = match.fighter1();
        Fighter& f2 = match.fighter2();

        FighterCommand c1 = controller.build(true);
        FighterCommand c2 = controller.build(false);

        physics.update(match, dt, c1, c2);

        pushboxSystem.resolve(match);

        stateMachine.update(f1, c1);
        stateMachine.update(f2, c2);

        animationSystem.update(f1, dt);
        animationSystem.update(f2, dt);

        f1.animation->update(dt);
        f2.animation->update(dt);

        combat.update(match, stateMachine);

        renderFrame(renderer, match);

        window.swapBuffers();
        window.pollEvents();
    }

    return 0;
}