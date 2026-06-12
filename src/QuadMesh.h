// src/QuadMesh.h
#pragma once

class QuadMesh
{
public:
    QuadMesh();
    ~QuadMesh();

    QuadMesh(const QuadMesh&) = delete;
    QuadMesh& operator=(const QuadMesh&) = delete;

    bool isValid() const;
    void draw() const;

private:
    unsigned int vao_ = 0;
    unsigned int vbo_ = 0;
    unsigned int ebo_ = 0;
};