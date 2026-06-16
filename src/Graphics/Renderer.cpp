#include "Renderer.h"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Renderer::Renderer(
    const Shader& shader,
    const QuadMesh& quad,
    const Texture& texture)
    :
    shader_(shader),
    quad_(quad),
    texture_(texture)
{
}

void Renderer::draw(
    const Transform& transform,
    Facing facing) const
{
    glm::mat4 model(1.0f);

    model = glm::translate(
        model,
        glm::vec3(
            transform.x,
            transform.y,
            0.0f));

    float scaleX =
        transform.width;

    if (facing == Facing::Left)
    {
        scaleX = -scaleX;
    }

    model = glm::scale(
        model,
        glm::vec3(
            scaleX,
            transform.height,
            1.0f));

    shader_.use();

    shader_.setMat4(
        "model",
        model);

    glActiveTexture(
        GL_TEXTURE0);

    texture_.bind();

    shader_.setInt(
        "texture0",
        0);

    quad_.draw();
}