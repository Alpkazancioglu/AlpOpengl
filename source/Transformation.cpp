#include "Transformation.h"
#include <iostream>

static glm::ivec2 windowSize;
static glm::vec2 inverseWindowSize;




Tranformation::Tranformation()
{

}

Tranformation::~Tranformation()
{

}

void Tranformation::SetModelMatrixUniform(GLuint shader, const char* uniform)
{
	glm::mat4 value = GetModelMat4();
	glUniformMatrix4fv((glGetUniformLocation(shader, uniform)),1,GL_FALSE,glm::value_ptr(value));
}

void Tranformation::Translate(glm::vec3 v3)
{
	TranslationMatrix = glm::translate(TranslationMatrix, v3);
}

void Tranformation::Scale(glm::vec3 v3)
{
	ScalingMatrix = glm::scale(ScalingMatrix, v3);
}

void Tranformation::Rotate(glm::vec3 v3, float angle)
{
	RotationMatrix = glm::rotate(RotationMatrix, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::ivec2 getWindowSize()
{
	return glm::ivec2(windowSize);
}

void updateWindowSize(GLFWwindow* window)
{
	glfwGetWindowSize(window, &windowSize.x, &windowSize.y);
	

	inverseWindowSize = 1.0 / glm::dvec2(windowSize);
}

glm::vec2 castScreenToClip(int x, int y)
{
	float xClip = (x + 0.5f) / (getWindowSize().x/2) - 1.0f;
	float yClip = 1.0f - (y + 0.5f) / (getWindowSize().y/2);
	return  glm::vec2(xClip, yClip);
}
