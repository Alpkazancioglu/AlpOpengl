#pragma once

#include "include.h"

#include <string>
#include <iostream>

class Texture
{
public:
	
	Texture(const std::string& path);
	
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unBind() const;
	unsigned int frameNumber;
	unsigned int currentFrame;

private:

	unsigned int m_id;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
};

