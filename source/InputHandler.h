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
       
        pressedKey.key = key;
        pressedKey.action = action;
    }
    static void PollInput(GLFWwindow* window)
    {
        if (pressedKey.action == GLFW_PRESS)
        {
           
            if (glfwGetKey(window, pressedKey.key) == GLFW_PRESS)
            {
                std::cout << "Key " << pressedKey.key << " is being pressed!" << std::endl;
            }
        }
        else if (pressedKey.action == GLFW_RELEASE)
        {
            static int counter = 0;
            if (counter == 1)
            {
                pressedKey.action = -1;
                counter = 0;
            }
            else
            {
                counter++;
                std::cout << "Key " << pressedKey.key << " has been released!" << pressedKey.action << std::endl;
            
            }
           
        }
    }

    static void InitInputHandler(GLFWwindow* window);
   
};

inline void InputHandler::InitInputHandler(GLFWwindow *window)
{
   
    glfwSetKeyCallback(window,key_callback);
}



