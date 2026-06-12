// src\TriangleMesh.h

#pragma once

class TriangleMesh
{
public:
    TriangleMesh();
    ~TriangleMesh();

    TriangleMesh(const TriangleMesh&) = delete;
    TriangleMesh& operator=(const TriangleMesh&) = delete;

    bool isValid() const;
    void draw() const;

private:
    unsigned int vao_ = 0;
    unsigned int vbo_ = 0;
};
