#pragma once

#include "glew.h"
#include "glfw3.h"




class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();


	void bind() const ;
	void unBind() const;
	


private:
	unsigned int m_id;
};

