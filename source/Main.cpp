
#include "Shader.h"
#include "Texture.h"
#include "Object.h"
#include "Camera.h"
#include "Engine.h"
#include "FrameBuffer.h"
#include "Character.h"





int main(void)
{

    PrimaryWindow = InitEngine();
    
    

    Shader shader("shaders/shader.vs","shaders/shader.fs");
    Texture killuaTex("resources/killua.png");
    Texture backgroundTex("resources/background.png");
    

    


    Camera2D camera(shader.getShader());
    
    //gon.transform.Translate(glm::vec3(2.0f, 2.0f, 0.0f));

    Character killua;
    killua.data.pos = { 0, 0 };
    killua.data.size = { 100,100 };
    killua.texture = &killuaTex;

    FrameBuffer frameBuffer;


    while (!glfwWindowShouldClose(PrimaryWindow))
    {
        /* Render here */
        frameBuffer.bind();
        deltaTime = getDeltaTime();
        InputHandler::PollInput(PrimaryWindow);
        

        glViewport(0, 0, frameBuffer.MonitorSize.x, frameBuffer.MonitorSize.y);
        updateWindowSize(PrimaryWindow);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f,1.0f,1.0f,1.0f);
        camera.UpdateCameraMatrix(glm::vec2(0.0f,0.0f), 1.0f);
        
        killua.move();
        
        drawRecTexture(shader,backgroundTex,{0,0},{1920,1080});
        drawRecTexture(shader,*killua.texture,killua.data.pos,killua.data.size);
        drawRectangle(shader,{0.0f,0.5f,0.0f},{0,880},{1920,200});    
        
        



        frameBuffer.unBind();
        frameBuffer.renderFbo();
        glfwSwapBuffers(PrimaryWindow);
       
        glfwPollEvents();
    }

    
    shader.clear();
    glfwTerminate();
    return 0;
}