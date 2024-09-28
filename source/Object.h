#pragma once

#include "Transformation.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include <memory>
#include "Texture.h"
#include "Shader.h"

#include "include.h"



#include "VertexBuffer.h"
#include "VertexBufferLayout.h"





struct Data
{
	glm::ivec2 pos;
	glm::ivec2 size;
	std::string name;
	bool isColliding;

};




class Object
{
public:
	Object();
	~Object();
	Data data;
	std::unique_ptr<Texture> texture;


private:
	


};

