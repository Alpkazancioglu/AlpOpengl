#pragma once
#include "include.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

glm::ivec2 getWindowSize();
void updateWindowSize(GLFWwindow* window);
glm::vec2 castScreenToClip(int x,int y);
glm::vec2 getViewPortSize();

class Tranformation
{
public:
	Tranformation();
	~Tranformation();

	glm::mat4 TranslationMatrix = glm::mat4(1.0f);
	glm::mat4 RotationMatrix = glm::mat4(1.0f);
	glm::mat4 ScalingMatrix = glm::mat4(1.0f);


	void SetModelMatrixUniform(GLuint shader, const char* uniform);
	virtual void Translate(glm::vec3 v3);
	void Scale(glm::vec3 v3);
	void Rotate(glm::vec3 v3, float angle);

	glm::mat4 GetModelMat4() { return TranslationMatrix * RotationMatrix * ScalingMatrix;}
	

private:

};

