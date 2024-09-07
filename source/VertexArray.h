#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unBind() const;

	void AddBuffer(VertexBuffer* vb, VertexBufferLayout* layout,IndexBuffer* ib);

private:
	unsigned int m_id;

};


