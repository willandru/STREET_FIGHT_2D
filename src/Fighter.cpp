#include "Fighter.h"

// =========================
// CONSTRUCTOR
// =========================

Fighter::Fighter()
{
    transform_.x = 0.6f;
    transform_.y = 0.20f;

    transform_.width = 0.30f;
    transform_.height = 0.30f;

    // DEFAULT HURTBOX (puedes ajustar luego por personaje)
    hurtbox_.offsetX = 0.0f;
    hurtbox_.offsetY = 0.0f;
    hurtbox_.width = 0.30f;
    hurtbox_.height = 0.30f;

    health_ = 100;
}

// =========================
// GETTERS
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
// COMBAT ACCESS
// =========================

const Hurtbox& Fighter::hurtbox() const { return hurtbox_; }
Hurtbox& Fighter::hurtbox() { return hurtbox_; }

const std::vector<Hitbox>& Fighter::hitboxes() const { return hitboxes_; }
std::vector<Hitbox>& Fighter::hitboxes() { return hitboxes_; }

// =========================
// COMMAND HANDLING
// =========================

void Fighter::applyCommand(const FighterCommand& cmd)
{
    // bloquear input durante ataques
    if (state_ == FighterState::LightAttack ||
        state_ == FighterState::HeavyAttack)
    {
        return;
    }

    crouching_ = cmd.crouch;

    // jump (solo intención, Physics aplica impulso real)
    if (cmd.jump && grounded_)
    {
        velocityY_ = JumpSpeed;
    }

    // attacks
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

    if (!grounded_)
    {
        state_ = FighterState::Jumping;
        return;
    }

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

// =========================
// COMBAT HELPERS
// =========================

bool Fighter::isAttackActive(const Hitbox& hit) const
{
    // versión mínima (luego la conectamos a animación/frame system)
    return (state_ == FighterState::LightAttack ||
            state_ == FighterState::HeavyAttack);
}

void Fighter::applyDamage(int dmg)
{
    health_ -= dmg;

    if (health_ < 0)
        health_ = 0;
}

int Fighter::health() const
{
    return health_;
}