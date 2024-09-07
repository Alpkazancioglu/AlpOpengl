#include "VertexArray.h"
#include <iostream>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_id);
}

void VertexArray::bind() const
{
	glBindVertexArray(m_id);

}

void VertexArray::unBind() const
{
	glBindVertexArray(0);
}


void VertexArray::AddBuffer(VertexBuffer* vb, VertexBufferLayout* layout,IndexBuffer* ib)
{
	bind();
	ib->bind();
	vb->bind();
	const auto& elements = layout->getElements();
	int offset = 0;
	for (size_t i = 0; i < elements.size(); i++)
	
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, elements[i].count, GL_FLOAT, GL_FALSE, layout->getStride(), (const void*)(offset*sizeof(float)));
		std::cout << offset << std::endl;
		offset += elements[i].count;

	}
	unBind();
	vb->unBind();
	ib->unBind();
}
