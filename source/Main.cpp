
#include "Shader.h"
#include "Texture.h"
#include "Object.h"
#include "Camera.h"
#include "Engine.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"



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



// Set the callback when initializing the window



int main(void)
{
    GLFWwindow* window;

   
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
   
    window = glfwCreateWindow(1600,900, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

   
    glfwMakeContextCurrent(window);



    if (glewInit() != GLEW_OK)
        return -1;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDebugMessageCallback(debugCallback, nullptr);
    
    
    


    Shader shader("shaders/shader.vs","shaders/shader.fs");

    
    Shader frameBufferShader("shaders/FrameBufferShader.vs", "shaders/FrameBufferShader.fs");




    InitEngine();


   
   
  
    shader.bind();
    Texture texture("resources/killua.png");
    texture.bind(0);
    
    shader.setUniform4f("uColor", 1.0f, 1.0f, 1.0f, 1.0f);
    shader.setUniform1i("uTexture", 0);
    shader.unBind();

    
   


    


    Camera2D camera(shader.getShader());
    
    //gon.transform.Translate(glm::vec3(2.0f, 2.0f, 0.0f));

    unsigned int frameBuffer;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    auto videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    unsigned int ScreenTexture;
    glGenTextures(1, &ScreenTexture);
    glBindTexture(GL_TEXTURE_2D, ScreenTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, videoMode->width, videoMode->height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ScreenTexture, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, videoMode->width, videoMode->height); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    



    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        
       
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        
        
        glViewport(0, 0, videoMode->width, videoMode->height);

        updateWindowSize(window);
       
       
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f,1.0f,1.0f,1.0f);

     

        camera.UpdateCameraMatrix(glm::vec2(0.0f,0.0f), 1.0f);

        drawRectangle(shader, { 0.0f,0.0f,0.0f }, { 400,400 }, { 800,800 },1.0f);
        
       

        
            
        









        glBindFramebuffer(GL_FRAMEBUFFER, 0);

       
        float currentWindowWidth = static_cast<float>(getWindowSize().x);
        float currentWindowHeight = static_cast<float>(getWindowSize().y);

        float Ratio = static_cast<float>(videoMode->width) / static_cast<float>(videoMode->height);
        float NewWidth = currentWindowHeight * Ratio;
        float NewHeight = currentWindowWidth / Ratio;

        if (NewWidth > NewHeight)
        {
            float posx = (currentWindowWidth - NewWidth) / 2.0f;
            glViewport(posx, 0.0f, NewWidth, currentWindowHeight);
        }
        if (NewWidth < NewHeight)
        {
            float posy = (currentWindowHeight - NewHeight) / 2.0f;
            glViewport(0.0f, posy, NewHeight, currentWindowHeight);
        }
        
        std::cout << NewWidth << "::" << NewHeight << std::endl;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(128.0f / 255.0f, 128.0f / 255.0f, 128.0f / 255.0f, 1.0f);


        frameBufferShader.bind();
        getQuadVao()->bind();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ScreenTexture);
        

        frameBufferShader.setUniform1i("viewport", 0);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


        
        frameBufferShader.unBind();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteFramebuffers(1, &frameBuffer);
    glDeleteRenderbuffers(1, &rbo);
    glDeleteTextures(1, &ScreenTexture);
    shader.clear();
    glfwTerminate();
    return 0;
}