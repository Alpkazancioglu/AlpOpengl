#include "Engine.h"


void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {

	const char* sourceStr;
	switch (source) {
	case GL_DEBUG_SOURCE_API: sourceStr = "API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM: sourceStr = "Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceStr = "Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY: sourceStr = "Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION: sourceStr = "Application"; break;
	case GL_DEBUG_SOURCE_OTHER: sourceStr = "Other"; break;
	default: sourceStr = "Unknown"; break;
	}

	const char* typeStr;
	switch (type) {
	case GL_DEBUG_TYPE_ERROR: typeStr = "Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeStr = "Deprecated Behavior"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: typeStr = "Undefined Behavior"; break;
	case GL_DEBUG_TYPE_PORTABILITY: typeStr = "Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE: typeStr = "Performance"; break;
	case GL_DEBUG_TYPE_MARKER: typeStr = "Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP: typeStr = "Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP: typeStr = "Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER: typeStr = "Other"; break;
	default: typeStr = "Unknown"; break;
	}

	const char* severityStr;
	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH: severityStr = "High"; break;
	case GL_DEBUG_SEVERITY_MEDIUM: severityStr = "Medium"; break;
	case GL_DEBUG_SEVERITY_LOW: severityStr = "Low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: severityStr = "Notification"; break;
	default: severityStr = "Unknown"; break;
	}


	fprintf(stderr, "OpenGL Debug Message:\n");
	fprintf(stderr, "    Source: %s\n", sourceStr);
	fprintf(stderr, "    Type: %s\n", typeStr);
	fprintf(stderr, "    ID: %u\n", id);
	fprintf(stderr, "    Severity: %s\n", severityStr);
	fprintf(stderr, "    Message: %s\n", message);
}



std::unique_ptr<VertexArray> vaoRec;
std::unique_ptr<VertexBuffer> vboRec;
VertexBufferLayout layout;
std::unique_ptr<IndexBuffer> ibRectangle;
Tranformation transMats;
bool IsMaximized = false;
glm::vec2 initSize;

void onMaximize(GLFWwindow* window, int maximized)
{
	IsMaximized = maximized == GLFW_TRUE ? true : false;
}

GLFWwindow* InitEngine()
{
	initSize = glm::vec2(1600, 900);
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
	GLFWwindow* window;


	if (!glfwInit())
		std::cout << "glfw init error" << std::endl;
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glm::vec2 initSize(1600, 900);
	window = glfwCreateWindow(initSize.x, initSize.y, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		std::cout << "window open error" << std::endl;
	}


	glfwMakeContextCurrent(window);



	if (glewInit() != GLEW_OK)
		std::cout << "glew init error" << std::endl;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDebugMessageCallback(debugCallback, nullptr);
	vaoRec = std::make_unique<VertexArray>();
	vboRec = std::make_unique<VertexBuffer>(positions, sizeof(positions));
	layout.Push(2);
	layout.Push(2);
	ibRectangle = std::make_unique<IndexBuffer>(rectangleIndices, sizeof(rectangleIndices));
	glfwSetWindowMaximizeCallback(window, onMaximize);

	vaoRec->AddBuffer(vboRec.get(), &layout,ibRectangle.get());

	return window;
};



void drawRectangleTexture(Shader& shader, Texture& texture, glm::vec2 position)
{

}


void drawRectangle(Shader& shader, glm::vec3 rgb, glm::vec2 pos,glm::vec2 size,float rotate)
{
	shader.bind();
	vaoRec->bind();
	glm::vec2 clipPos = castScreenToClip(pos.x, pos.y);

	float clipWidth = size.x / (initSize.x / 2.0f);
	float clipHeight = size.y / (initSize.y / 2.0f);
	std::cout << getViewPortSize().x << std::endl;



	
	transMats.TranslationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(clipPos.x, clipPos.y,0.0f));
	transMats.ScalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(clipWidth, clipHeight, 1.0f));

	

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
