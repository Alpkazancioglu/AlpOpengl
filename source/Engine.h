#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include <memory>
#include "Shader.h"
#include "include.h"
#include "InputHandler.h"


#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Transformation.h"
#include <iostream>

extern float deltaTime;

extern bool IsMaximized;
extern GLFWwindow* PrimaryWindow; 
GLFWwindow* InitEngine();
void drawRectangle(Shader& shader,  glm::vec3 rgb, glm::vec2 pos, glm::vec2 size, float rotate = 1.0f);
void drawRecTexture(Shader& shader,Texture& texture,glm::vec2 pos, glm::vec2 size, float rotate = 1.0f);
float getDeltaTime();




VertexArray* getQuadVao();







