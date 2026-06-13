#pragma once

class Stage
{
public:

    float groundY() const;
    float leftBoundary() const;
    float rightBoundary() const;

private:

    float groundY_ = -0.80f;

    float leftBoundary_ = -1.0f;
    float rightBoundary_ = 1.0f;
};  