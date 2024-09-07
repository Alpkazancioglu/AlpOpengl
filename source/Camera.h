#pragma once
#include "glew.h"
#include "glfw3.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


class Camera2D
{
public:
	Camera2D(unsigned int shader);
	~Camera2D();

	void SetViewMatrixUniformLocation(GLuint shader, const char* uniform);
	void SetProjMatrixUniformLocation(GLuint shader, const char* uniform);
	void SetCameraMatrixUniformLocation(GLuint shader, const char* uniform);
	
	void SetRatioMatrixUniformLocation(GLuint shader, const char* uniform);
	void UpdateCameraMatrix(glm::vec2 pos, float zoom);

private:
	
	glm::mat4 viewMat;
	glm::mat4 projMat;
	glm::mat4 CameraMat;
	glm::mat4 RatioMat;
	glm::mat4 ProjectionViewMat;
	unsigned int shaderID;
};
glm::vec2 GetScreenRatio(glm::ivec2 windowSize);