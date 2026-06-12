#include "Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Renderer::Renderer(
    const Shader& shader,
    const QuadMesh& quad)
    :
    shader_(shader),
    quad_(quad)
{
}

void Renderer::draw(
    const Transform& transform) const
{
    glm::mat4 model(1.0f);

    model = glm::translate(
        model,
        glm::vec3(
            transform.x,
            transform.y,
            0.0f));

    model = glm::scale(
        model,
        glm::vec3(
            transform.width,
            transform.height,
            1.0f));

    shader_.use();

    shader_.setMat4(
        "model",
        model);

    quad_.draw();
}