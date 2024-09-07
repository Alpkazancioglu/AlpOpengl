#pragma once

#include "Transformation.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include <memory>
#include "Texture.h"
#include "Shader.h"


#include "glew.h"
#include "glfw3.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <fwd.hpp>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"




struct data
{

};




class Object
{
public:
	Object();
	~Object();
	void drawRecTexture(Shader& shader,Texture& texture);
	void DrawRec(Shader& shader, glm::vec3 rgb);
	void drawTriangle();
	void setPos(glm::vec2 pos);
	void move();


	Tranformation transform;
	
	

	
	


private:
	
	VertexArray vao;
	std::unique_ptr<VertexBuffer> vbo;
	std::unique_ptr<IndexBuffer> ib;
	VertexBufferLayout layout;
	

};

