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

};




class Object
{
public:
	Object();
	~Object();
	Data data;
	


private:
	


};

