// src\TriangleMesh.cpp

#include "TriangleMesh.h"

#include <glad/glad.h>

TriangleMesh::TriangleMesh()
{
    constexpr float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };

    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);

    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

TriangleMesh::~TriangleMesh()
{
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
}

bool TriangleMesh::isValid() const
{
    return vao_ != 0 && vbo_ != 0;
}

void TriangleMesh::draw() const
{
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
