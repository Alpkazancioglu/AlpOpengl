#include "Engine.h"






std::unique_ptr<VertexArray> vaoRec;
std::unique_ptr<VertexBuffer> vboRec;
VertexBufferLayout layout;
std::unique_ptr<IndexBuffer> ibRectangle;
Tranformation transMats;


void InitEngine()
{
	const float positions[] = {
		   -0.5f,0.5f,        0.0f,1.0f,  // 0
		   0.5f, 0.5f,        1.0f,1.0f,   // 1
		   -0.5f,-0.5f,       0.0f,0.0f, // 2
		   0.5f , -0.5f,      1.0f , 0.0f // 3

	};
	const unsigned int rectangleIndices[6] = {
		0,1,2,
		1,2,3
	};
	vaoRec = std::make_unique<VertexArray>();
	vboRec = std::make_unique<VertexBuffer>(positions, sizeof(positions));
	layout.Push(2);
	layout.Push(2);
	ibRectangle = std::make_unique<IndexBuffer>(rectangleIndices, sizeof(rectangleIndices));


	vaoRec->AddBuffer(vboRec.get(), &layout,ibRectangle.get());


};



void drawRectangleTexture(Shader& shader, Texture& texture, glm::vec2 position)
{

}


void drawRectangle(Shader& shader, glm::vec3 rgb, glm::vec2 pos,glm::vec2 size,float rotate)
{
	shader.bind();
	vaoRec->bind();
	glm::vec2 clipPos = castScreenToClip(pos.x, pos.y);
	glm::vec2 clipWidthAndHeight = castScreenToClip(size.x, size.y);

	
	transMats.TranslationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));
	transMats.ScalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f,1.0f, 1.0f));

	

	transMats.SetModelMatrixUniform(shader.getShader(), "model");
	shader.setUniform1i("colorFlag", RGBCOLOR);
	shader.setUniform3f("uColor", rgb.x, rgb.y, rgb.z);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	vaoRec->unBind();
	shader.unBind();

}
const VertexArray* getQuadVao()
{


	return vaoRec.get();
}
