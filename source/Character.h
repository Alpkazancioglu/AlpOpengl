#pragma once
#include "Object.h"
#include "Texture.h"
#include "Engine.h"



class Character : public Object
{
private:
    /* data */
public:
    Character(/* args */);
    ~Character();
    void move();
};

Character::Character(/* args */)
{
}

Character::~Character()
{
}

inline void Character::move()
{
    if (glfwGetKey(PrimaryWindow,GLFW_KEY_D) == GLFW_PRESS)
    {
        std::cout << "left" << '\n';
    }
}
