
#include "Shader.h"
#include "Texture.h"
#include "Object.h"
#include "Camera.h"
#include "Engine.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"







// Set the callback when initializing the window



int main(void)
{
    GLFWwindow* window = InitEngine();

    Shader shader("shaders/shader.vs","shaders/shader.fs");
    Shader frameBufferShader("shaders/FrameBufferShader.vs", "shaders/FrameBufferShader.fs");

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

        drawRectangle(shader, { 0.0f,0.0f,0.0f }, { 0,0 }, { 1600/2,900/2 },1.0f);
        
       

        
            
        









        glBindFramebuffer(GL_FRAMEBUFFER, 0);

       
        double currentWindowWidth = static_cast<double>(getWindowSize().x);
        double currentWindowHeight = IsMaximized ? static_cast<double>(videoMode->height) : static_cast<double>(getWindowSize().y);

        double Ratio = static_cast<double>(videoMode->width) / static_cast<double>(videoMode->height);

        double NewWidth = currentWindowHeight * Ratio;
        double NewHeight = currentWindowWidth / Ratio;

        if (currentWindowWidth > currentWindowHeight)
        {
            if (currentWindowWidth > NewWidth)
            {
                double posx = (currentWindowWidth - NewWidth) / 2.0;
                glViewport(posx, 0.0, NewWidth, currentWindowHeight);
            }
            else
            {
                double posy = (currentWindowHeight - NewHeight) / 2.0;
                glViewport(0.0f, posy, currentWindowWidth, NewHeight);
            }
        }
        else if (currentWindowWidth < currentWindowHeight)
        {
            double posy = (currentWindowHeight - NewHeight) / 2.0;
            glViewport(0.0, posy, currentWindowWidth, NewHeight);
        }
        
       
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