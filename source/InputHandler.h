#pragma once
#include "include.h"
#include <iostream>


struct s_InputHandler
{
    unsigned int key;
    unsigned int action;
};

extern s_InputHandler pressedKey;


class InputHandler
{

public:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        std::cout << key << '\n';
        pressedKey.key = key;
        pressedKey.action = action;
    }
    static void InitInputHandler(GLFWwindow* window);
    InputHandler();
    ~InputHandler();
};

inline void InputHandler::InitInputHandler(GLFWwindow *window)
{
    glfwSetKeyCallback(window,key_callback);
}



