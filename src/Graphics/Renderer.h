#pragma once

#include "QuadMesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "Facing.h"

class Renderer
{
public:
    Renderer(
        const Shader& shader,
        const QuadMesh& quad,
        const Texture& texture);

    void draw(
        const Transform& transform,
        Facing facing) const;

private:
    const Shader& shader_;
    const QuadMesh& quad_;
    const Texture& texture_;
};