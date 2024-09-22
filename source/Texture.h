#pragma once

#include "include.h"

#include <string>
#include <iostream>

class Texture
{
public:
	
	Texture();
	Texture(const std::string& path);
	
	
	

	~Texture();

	void bind(unsigned int slot = 0) const;
	void unBind() const;
	
	Texture  operator == (Texture const& other)
	{
		Texture texture;
		texture.m_id = other.m_id;
		return texture;
	}

	static std::unique_ptr<Texture> LoadTexture(const std::string& path)
	{
		return std::make_unique<Texture>(path);
	}


private:

	unsigned int m_id;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
};

