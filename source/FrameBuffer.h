#pragma once

#include "include.h"
#include "Shader.h"
#include <iostream>
#include "Engine.h"


class FrameBuffer
{
private:
    unsigned int m_frameBuffer;
    unsigned int m_renderBuffer;
    unsigned int m_ScreenTexture;
    void resizeFbo();
    VertexArray* vao;
    std::unique_ptr<Shader> shader;
public:
    void bind();
    void unBind();
    glm::vec2 MonitorSize;
    void renderFbo();
    FrameBuffer();
    ~FrameBuffer();
};

FrameBuffer::FrameBuffer()
{
    
    glGenFramebuffers(1, &m_frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

    auto videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    MonitorSize = glm::vec2(videoMode->width,videoMode->height);
    std::cout << MonitorSize.x << "::" << MonitorSize.y << std::endl;
    
    glGenTextures(1, &m_ScreenTexture);
    glBindTexture(GL_TEXTURE_2D, m_ScreenTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, MonitorSize.x, MonitorSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ScreenTexture, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    
    glGenRenderbuffers(1, &m_renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, MonitorSize.x, MonitorSize.y); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBuffer); // now actually attach it
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    


    vao = getQuadVao();
    shader = std::make_unique<Shader>("shaders/FrameBufferShader.vs", "shaders/FrameBufferShader.fs");


}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1,&m_frameBuffer);
    glDeleteRenderbuffers(1,&m_renderBuffer);
    glDeleteTextures(1,&m_ScreenTexture);
    shader->clear();
    delete(vao);
}

void FrameBuffer::resizeFbo()
{
        double currentWindowWidth = static_cast<double>(getWindowSize().x);
        double currentWindowHeight = IsMaximized ? static_cast<double>(MonitorSize.y) : static_cast<double>(getWindowSize().y);

        double Ratio = static_cast<double>(MonitorSize.x) / static_cast<double>(MonitorSize.y);

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
}

inline void FrameBuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER,m_frameBuffer);
}

inline void FrameBuffer::unBind()
{
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void FrameBuffer::renderFbo()
{
        resizeFbo();
        shader->bind();
        vao->bind();
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_ScreenTexture);
        shader->setUniform1i("viewport", 0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        
        vao->unBind();
        shader->unBind();
}