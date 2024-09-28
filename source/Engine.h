#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include <memory>
#include "Shader.h"
#include "include.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Transformation.h"
#include <iostream>
#include "Log.h"
#define GRAVITY 10.0f



extern bool IsMaximized;


namespace ENGINE {
	inline float deltaTime = 0;
	inline GLFWwindow* window = nullptr;
	GLFWwindow* GetWindow();
	extern float gravity;
	
	void InitEngine();
	void drawRectangle(Shader& shader, glm::vec3 rgb, glm::vec2 pos, glm::vec2 size, float rotate = 1.0f);
	void drawRecTexture(Shader& shader, Texture& texture, glm::vec2 pos, glm::vec2 size, float rotate = 1.0f);
	float getDeltaTime();
	VertexArray* getQuadVao();
}









