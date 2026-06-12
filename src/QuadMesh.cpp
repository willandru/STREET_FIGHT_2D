#include "QuadMesh.h"

#include <glad/glad.h>

QuadMesh::QuadMesh()
{
    // Rectángulo centrado en el origen
    const float vertices[] =
    {
        // x      y      z
        -0.5f, -0.5f, 0.0f, // 0
         0.5f, -0.5f, 0.0f, // 1
         0.5f,  0.5f, 0.0f, // 2
        -0.5f,  0.5f, 0.0f  // 3
    };

    const unsigned int indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ebo_);

    if (vao_ == 0 || vbo_ == 0 || ebo_ == 0)
    {
        return;
    }

    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(indices),
        indices,
        GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,                  // location
        3,                  // x,y,z
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        nullptr);

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

QuadMesh::~QuadMesh()
{
    if (ebo_ != 0)
    {
        glDeleteBuffers(1, &ebo_);
    }

    if (vbo_ != 0)
    {
        glDeleteBuffers(1, &vbo_);
    }

    if (vao_ != 0)
    {
        glDeleteVertexArrays(1, &vao_);
    }
}

bool QuadMesh::isValid() const
{
    return vao_ != 0 &&
           vbo_ != 0 &&
           ebo_ != 0;
}

void QuadMesh::draw() const
{
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}