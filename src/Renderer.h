#pragma once

#include "QuadMesh.h"
#include "Shader.h"
#include "Transform.h"

class Renderer
{
public:
    Renderer(
        const Shader& shader,
        const QuadMesh& quad);

    void draw(
        const Transform& transform) const;

private:
    const Shader& shader_;
    const QuadMesh& quad_;
};