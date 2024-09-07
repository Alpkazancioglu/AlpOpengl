#include "Shader.h"


Shader::Shader(const char* VertexShaderFilePath, const char* FragmentShaderFilePath) {

	std::string VertexShaderSource = ParseShader(VertexShaderFilePath);
	std::string FragmentShaderSource = ParseShader(FragmentShaderFilePath);

	shaderId = CreateProgram(VertexShaderSource, FragmentShaderSource);

}


void Shader::clear()
{
	glDeleteProgram(shaderId);
}

GLuint Shader::getShader()
{
	return shaderId;
}

void Shader::bind() const
{
	glUseProgram(shaderId);
}

void Shader::unBind() const
{
	glUseProgram(0);
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(glGetUniformLocation(shaderId, name.c_str()), v0, v1, v2, v3);

}

void Shader::setUniform3f(const std::string& name, float v0, float v1, float v2)
{
	glUniform3f(glGetUniformLocation(shaderId, name.c_str()), v0, v1, v2);
}

void Shader::setUniform1i(const std::string& name, int v)
{
	glUniform1i(glGetUniformLocation(shaderId, name.c_str()), v);
}

void Shader::setUniformMat4(const std::string& name, glm::mat4& data)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE, glm::value_ptr(data));
}





