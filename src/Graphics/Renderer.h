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
        const QuadMesh& quad);

    void draw(
        const Transform& transform,
        Facing facing,
        const Texture& texture) const;

private:
    const Shader& shader_;
    const QuadMesh& quad_;
};