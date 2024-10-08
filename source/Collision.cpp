#include "Collision.h"

bool IsCollidingRecToRec(Data &obj1, Data &obj2)
{
    bool collisionX = obj1.pos.x + obj1.size.x >= obj2.pos.x &&
        obj2.pos.x + obj2.size.x >= obj1.pos.x;
    
    bool collisionY = obj1.pos.y + obj1.size.y >= obj2.pos.y &&
        obj2.pos.y + obj2.size.y >= obj1.pos.y;
    
    return collisionX && collisionY;
    
}

std::vector<Data> IsCollidingWithObjectsArray(Data& obj,std::vector<Data>& objects)
{
    std::vector<Data> collidingObjects;
    for (size_t i = 0; i < objects.size(); i++)
    {
        if (obj.name != objects[i].name)
        {
            collidingObjects.push_back(objects[i]);
            if (IsCollidingRecToRec(obj,objects[i]))
            {
                LOG(objects[i].name);
                
            }
            
                
        }
    }

    if (collidingObjects)
    return collidingObjects;
    
}

