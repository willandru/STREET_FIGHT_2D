#pragma once

struct GLFWwindow;

enum class Key
{
    W,
    A,
    S,
    D,
    Space
};

class Input
{
public:
    static void Initialize(
        GLFWwindow* window);

    static bool IsKeyDown(
        Key key);

private:
    static GLFWwindow* window_;
};