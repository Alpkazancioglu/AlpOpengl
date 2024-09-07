#include "Camera.h"
#include "Engine.h"

Camera2D::Camera2D(unsigned int shader)
{

	viewMat = glm::mat4(1.0f);
	projMat = glm::mat4(1.0f);
	
	
	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
	
	//viewMat = glm::scale(viewMat, glm::vec3(-2.0f, -2.0f, 1.0f));

	shaderID = shader;
	
	glUseProgram(shaderID);
	
	SetViewMatrixUniformLocation(shaderID, "view");
	SetProjMatrixUniformLocation(shaderID, "projection");
	glUseProgram(0);
}

Camera2D::~Camera2D()
{

}

void Camera2D::SetViewMatrixUniformLocation(GLuint shader, const char* uniform)
{
	glUniformMatrix4fv((glGetUniformLocation(shader, uniform)), 1, GL_FALSE,&viewMat[0][0]);
}

void Camera2D::SetProjMatrixUniformLocation(GLuint shader, const char* uniform)
{
	glUniformMatrix4fv((glGetUniformLocation(shader, uniform)), 1, GL_FALSE, &projMat[0][0]);
}

void Camera2D::SetCameraMatrixUniformLocation(GLuint shader, const char* uniform)
{

}




void Camera2D::SetRatioMatrixUniformLocation(GLuint shader, const char* uniform)
{

}

void Camera2D::UpdateCameraMatrix(glm::vec2 pos,float zoom)
{
	
	glm::mat4 ratioMat = glm::scale(glm::mat4(1.0f), glm::vec3(GetScreenRatio(getWindowSize()).x, GetScreenRatio(getWindowSize()).y, 1.0f));
	projMat = glm::ortho((-1.0f + pos.x) / zoom, (1.0f + pos.x) / zoom, (-1.0f + pos.y) / zoom, (1.0f + pos.y) / zoom, -5.0f, 5.0f);
	viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	

	
	
	glUseProgram(shaderID);


	
	SetProjMatrixUniformLocation(shaderID, "projection");
	SetViewMatrixUniformLocation(shaderID,"view");
	glUseProgram(0);

}
glm::vec2 GetScreenRatio(glm::ivec2 windowSize)
{
	

	float aspectRatios_wh = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
	float aspectRatios_hw = static_cast<float>(windowSize.y) / static_cast<float>(windowSize.x);

	float ratio_minmax_x = 1.0f, ratio_minmax_y = 1.0f;
	
	ratio_minmax_x = aspectRatios_wh;
	ratio_minmax_y = aspectRatios_hw;
	
	/*if (windowSize.y > windowSize.x)
	{
		ratio_minmax_x = aspectRatios_hw;
		
	}
	else if (windowSize.y < windowSize.x)
	{

		ratio_minmax_y = aspectRatios_wh;

	}*/
	
	

	return glm::vec2(ratio_minmax_x, ratio_minmax_y);
}