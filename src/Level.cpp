#include "Level.h"

Level::Level()
{
    // Suelo principal
    platforms_.emplace_back(
        0.0f,
        -0.80f,
        2.0f,
        0.05f);

    // Plataforma izquierda
    platforms_.emplace_back(
        -0.60f,
        -0.20f,
        0.50f,
        0.10f);

    // Plataforma central
    platforms_.emplace_back(
        0.00f,
        0.10f,
        0.50f,
        0.10f);

    // Plataforma derecha
    platforms_.emplace_back(
        0.60f,
        0.40f,
        0.40f,
        0.10f);
}

const Player& Level::player() const
{
    return player_;
}

Player& Level::player()
{
    return player_;
}

const std::vector<Platform>& Level::platforms() const
{
    return platforms_;
}

std::vector<Platform>& Level::platforms()
{
    return platforms_;
}