#pragma once

#include "glew.h"
#include "glfw3.h"

#include <string>
#include <iostream>

class Texture
{
public:
	
	Texture(const std::string& path);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unBind() const;

private:
	unsigned int m_id;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
};

