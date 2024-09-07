#pragma once
#include <vector>
#include "glew.h"
#include "glfw3.h"


class VertexBufferLayout
{
	struct VertexBufferElement
	{
		unsigned int type;
		unsigned int count;

	};

public:
	VertexBufferLayout();
	~VertexBufferLayout();
	
	
	void Push(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT,count});
		m_stride += sizeof(GLfloat) * count;
	
	}
	unsigned int getStride() const { return m_stride; }
	const std::vector<VertexBufferElement> getElements() const& { return m_Elements;}


private:
	
	unsigned int m_stride;
	std::vector<VertexBufferElement> m_Elements;

};
