#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include <memory>
#include "Shader.h"
#include "include.h"


#include "Texture.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Transformation.h"
#include <iostream>


void InitEngine();
void drawRectangle(Shader& shader, glm::vec3 rgb, glm::vec2 pos, glm::vec2 size, float rotate);

const VertexArray* getQuadVao();







