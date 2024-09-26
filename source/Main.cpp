#include "Engine.h"
#include "Shader.h"
#include "Texture.h"
#include "Object.h"
#include "Camera.h"
#include "FrameBuffer.h"
#include "Character.h"
#include <unordered_map>
#include "InputHandler.h"
#include <chrono>
#include <thread>
#include "Collision.h"
#include <vector>



const double TARGET_FRAME_TIME = 1.0 / 60;













int main(void)
{

    ENGINE::InitEngine();
    
    
    
    Shader shader("shaders/shader.vs","shaders/shader.fs");
    
    Texture backgroundTex("resources/background.png");
 
    Camera2D camera(shader.getShader());
    
    //gon.transform.Translate(glm::vec3(2.0f, 2.0f, 0.0f));

    Character killua;
    Object ground;

    ground.data.pos = {0,880};
    ground.data.size = {1920,200};
    
    killua.data.pos = { 0, 0 };
    killua.data.size = { 180,180 };
   

    killua.texture = Texture::LoadTexture("resources/knight.png");
  
    
    std::vector<Data> objectDatas;

    FrameBuffer frameBuffer;

    
    INPUT::InitInputHandler();
    

    objectDatas.push_back(killua.data);
    objectDatas.push_back(ground.data);
    
    
    


    while (!glfwWindowShouldClose(ENGINE::GetWindow()))
    {
       
        frameBuffer.bind();
        ENGINE::deltaTime = ENGINE::getDeltaTime();
        
        

        glViewport(0, 0, frameBuffer.MonitorSize.x, frameBuffer.MonitorSize.y);
        updateWindowSize(ENGINE::GetWindow());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.5f,0.5f,0.5f,1.0f);
        camera.UpdateCameraMatrix(glm::vec2(0.0f,0.0f), 1.0f);
        
        killua.move();
        
        ENGINE::drawRecTexture(shader,backgroundTex,{0,0},{1920,1080});
        
        ENGINE::drawRecTexture(shader,*killua.texture,killua.data.pos,killua.data.size);
        ENGINE::drawRectangle(shader,{0.0f,0.5f,0.0f},ground.data.pos,ground.data.size);
       
       

        if (IsCollidingRecToRec(killua.data,ground.data))
            std::cout << "collision" << killua.data.pos.y  << "::" << ground.data.pos.y<< '\n';
        else
            std::cout << " no collision" << '\n';






        INPUT::UpdateKeys();
        frameBuffer.unBind();
        frameBuffer.renderFbo();
        glfwSwapBuffers(ENGINE::GetWindow());
       
        glfwPollEvents();


    }

    
    shader.clear();
    glfwTerminate();
    return 0;
}