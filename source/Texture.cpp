#include "Texture.h"
#include "stb_image.h"


Texture::Texture(const std::string& path):
	m_FilePath(path), m_LocalBuffer(0), m_Width(0), m_Height(0) , m_BPP(0), m_id(0)
{
	
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, NULL);
	if (!m_LocalBuffer)
	{
		std::cout << "aradaginiz texture suan ulasilamiyor ::  "  << '\n';
	}
	GLenum format;

	if (m_BPP == 1)
	{
		format = GL_RED;
	}
	else if (m_BPP == 3)
	{
		format = GL_RGB;
	}
	else if (m_BPP == 4)
	{
		format = GL_RGBA;
	}
	else
	{
		std::cout << "oh no texture format is wrong :: "<< '\n';
		return;
	}


	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);
	
	glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_LocalBuffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
	}
	else
	{
		std::cout << "\nError: Failed to load texture" << std::endl;
		std::cout << stbi_failure_reason() << std::endl;
		__debugbreak();
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

void Texture::bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
