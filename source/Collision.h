#pragma once
#include "Object.h"
#include "Engine.h"

struct CollisionData
{
    bool IsColliding;
    std::string CollidingWith;
    int direction;

};


bool IsCollidingRecToRec(Data& obj1,Data& obj2);
std::vector<Data> IsCollidingWithObjectsArray(Data& obj,std::vector<Data>& objects);