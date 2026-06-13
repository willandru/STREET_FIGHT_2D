#include "Fighter.h"

// =========================
// CONSTRUCTOR
// =========================
Fighter::Fighter()
{
    transform_.x = 0.6f;
    transform_.y = 0.2f;

    transform_.width = 0.3f;
    transform_.height = 0.3f;

    hurtbox_.offsetX = 0.0f;
    hurtbox_.offsetY = 0.0f;
    hurtbox_.width = 0.3f;
    hurtbox_.height = 0.3f;

    health_ = 100;

    state_ = FighterState::Idle;
    facing_ = Facing::Right;

    velocityX_ = 0.0f;
    velocityY_ = 0.0f;

    grounded_ = false;
    crouching_ = false;
}

// =========================
// TRANSFORM
// =========================
const Transform& Fighter::transform() const { return transform_; }
Transform& Fighter::transform() { return transform_; }

// =========================
// MOVEMENT
// =========================
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
// COMBAT DATA
// =========================
const Hurtbox& Fighter::hurtbox() const { return hurtbox_; }
Hurtbox& Fighter::hurtbox() { return hurtbox_; }

const std::vector<Hitbox>& Fighter::hitboxes() const { return hitboxes_; }
std::vector<Hitbox>& Fighter::hitboxes() { return hitboxes_; }

// =========================
// HEALTH
// =========================
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