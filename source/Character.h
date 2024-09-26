#pragma once
#include "Object.h"
#include "Texture.h"
#include "Engine.h"
#include "InputHandler.h"


class Character : public Object
{
private:
    /* data */
public:
    bool isColliding;
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
   
    
    if (!isColliding)
        this->data.pos.y += 10;


    if (INPUT::IsKeyDown(GLFW_KEY_D))
        this->data.pos.x += 10;
    if (INPUT::IsKeyDown(GLFW_KEY_A))
        this->data.pos.x -= 10;
   /* if (INPUT::IsKeyDown(GLFW_KEY_S) && !isColliding)
        this->data.pos.y += 10;*/
    if (INPUT::IsKeyPressed(GLFW_KEY_SPACE))
        this->data.pos.y -= 250;
}
