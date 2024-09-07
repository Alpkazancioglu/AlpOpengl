#pragma once
#include "include.h"


class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data,unsigned int size);
	~IndexBuffer();

	void bind() const;
	void unBind() const;

private:
	unsigned int m_id;
};

