#include "Fighter.h"
#include "FighterCommand.h"

Fighter::Fighter()
{
    transform_.x = 0.6f;
    transform_.y = 0.20f;

    transform_.width = 0.30f;
    transform_.height = 0.30f;
}

// =========================
// GETTERS / SETTERS
// =========================

const Transform& Fighter::transform() const { return transform_; }
Transform& Fighter::transform() { return transform_; }

float Fighter::velocityX() const { return velocityX_; }
float& Fighter::velocityX() { return velocityX_; }

float Fighter::velocityY() const { return velocityY_; }
float& Fighter::velocityY() { return velocityY_; }

bool Fighter::grounded() const { return grounded_; }
bool& Fighter::grounded() { return grounded_; }

bool Fighter::crouching() const { return crouching_; }
bool& Fighter::crouching() { return crouching_; }

Facing Fighter::facing() const { return facing_; }
Facing& Fighter::facing() { return facing_; }

FighterState Fighter::state() const { return state_; }
FighterState& Fighter::state() { return state_; }

// =========================
// COMMAND APPLICATION
// =========================

void Fighter::applyCommand(const FighterCommand& cmd)
{
    // =========================
    // BLOCK INPUT DURING ATTACK
    // =========================

    if (state_ == FighterState::LightAttack ||
        state_ == FighterState::HeavyAttack)
    {
        return;
    }

    // =========================
    // RESET PER FRAME INPUT
    // =========================

    velocityX_ = 0.0f;
    crouching_ = false;

    // =========================
    // MOVEMENT
    // =========================

    if (cmd.moveLeft)
        velocityX_ = -MoveSpeed;

    if (cmd.moveRight)
        velocityX_ = MoveSpeed;

    // =========================
    // JUMP
    // =========================

    if (cmd.jump && grounded_)
        velocityY_ = JumpSpeed;

    // =========================
    // CROUCH
    // =========================

    if (cmd.crouch)
        crouching_ = true;

    // =========================
    // ATTACKS (STATE INIT)
    // =========================

    if (cmd.lightAttack && state_ == FighterState::Idle)
    {
        state_ = FighterState::LightAttack;
        stateTimer_ = 20.0f;
    }

    if (cmd.heavyAttack && state_ == FighterState::Idle)
    {
        state_ = FighterState::HeavyAttack;
        stateTimer_ = 35.0f;
    }
}

// =========================
// STATE MACHINE
// =========================

void Fighter::updateState()
{
    // =========================
    // ATTACK STATE HANDLING
    // =========================

    if (state_ == FighterState::LightAttack ||
        state_ == FighterState::HeavyAttack)
    {
        stateTimer_ -= 1.0f;

        if (stateTimer_ <= 0.0f)
        {
            state_ = grounded_ ? FighterState::Idle : FighterState::Jumping;
        }

        return;
    }

    // =========================
    // AIR STATE
    // =========================

    if (!grounded_)
    {
        state_ = FighterState::Jumping;
        return;
    }

    // =========================
    // GROUND STATES
    // =========================

    if (crouching_)
    {
        state_ = FighterState::Crouching;
        return;
    }

    if (velocityX_ != 0.0f)
    {
        state_ = FighterState::Walking;
        return;
    }

    state_ = FighterState::Idle;
}