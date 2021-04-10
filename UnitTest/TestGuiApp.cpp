//
//  TestGuiApp.c
//  test_gui
//
//  Reference:
//      https://eliasdaler.github.io/using-imgui-with-sfml-pt2/
//      https://programmersought.com/article/64656113270/
//      https://learnopengl.com/Advanced-OpenGL/Framebuffers
//      https://gamedev.stackexchange.com/questions/150214/render-in-a-imgui-window
//  Created by kenlee on 14/3/2021.
//
#include <iostream>

#include "TestGuiApp.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"


void SampleGuiApp1::onInit()
{
    _clearColor = ImVec4(1.0f, 0.55f, 0.60f, 1.00f);
    
}


void SampleGuiApp1::onUpdate(double delta)
{
    bool flag;
    ImGui::ShowDemoWindow(&flag);
    
    // A new window
    ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");   // Label inside the window
    
    ImGui::End();
    
    //
    
    if(ImGui::Begin("First Window"))
    {
    ImGui::Text("Do you like it?");
    ImGui::Button("Yes");
    ImGui::Button("No");
    ImGui::End();
    }
}

// ---------


//https://www.programmersought.com/article/85304753942/
void SampleGuiApp2::drawShapes()
{
    auto* drawList = ImGui::GetBackgroundDrawList();

    // Origin call
    drawList->AddTriangleFilled(ImVec2(30, 10),
                                ImVec2(20, 30),
                                ImVec2(40, 30),
                                ImColor(255, 0, 0));
    //drawList->Add
    SNShapeHelper::drawTriangleAtCenter(ImVec2(100, 50), 10, ImColor(0, 255, 0));
    
    
    SNShapeHelper::drawRectAtCenter(ImVec2(100, 250), 50, ImColor(0, 255, 0));
    
    // Active position position
    SNShapeHelper::drawRectAtCenter(_pos, 30, ColorYellow);
    //SNShapeHelper::drawRectAtCenter(ImVec2(100, 250), 50, ImColor(0, 255, 0));
}

void SampleGuiApp2::onInit()
{
    _clearColor = ImVec4(0.5f, 0.5f, 0.50f, 1.00f);
    _pos = ImVec2(100, 300);
}

void SampleGuiApp2::onUpdate(double delta)
{
    
    handleInput(delta);
    
    // GUI Handling
    // A new window
    ImGui::Begin("Testing Primitive!"); // Create a window called "Hello, world!" and append into it.

    
    if (ImGui::Button("Button A")) {
        std::cout << "'Button A' is clicked\n";
    }
    ImGui::Text("Text Line 1");
    ImGui::Text("Text Line 2");
    ImGui::Text("Text Line with variable %s", "hello");
    ImGui::End();
    
    // END of GUI Handling
    
    drawShapes();
}

void SampleGuiApp2::handleInput(double deltaTime)
{
    ImVec2 dir {0,0};
    float speed = 200;

    if (getInputKey(SDLK_w)) dir.y -= 1;
    if (getInputKey(SDLK_s)) dir.y += 1;
    if (getInputKey(SDLK_a)) dir.x -= 1;
    if (getInputKey(SDLK_d)) dir.x += 1;

    _pos.x += dir.x * deltaTime * speed;
    _pos.y += dir.y * deltaTime * speed;
}

#pragma mark - Sample Particle App
SampleParticleApp::SampleParticleApp()
: _pSystem()
{
    
}


void SampleParticleApp::onInit()
{
    _clearColor = ImVec4(0.0f, 0.0f, 0.10f, 1.00f);
    
}


void SampleParticleApp::onUpdate(double delta)
{
    handleInput(delta);
    
    bool flag;
    
    _pSystem.onUpdate(delta);
    
    SNShapeHelper::drawCircleAtCenter(ImVec2(100, 100), 2, ColorRed);
    
    ImGui::Begin("Testing", NULL, ImGuiWindowFlags_AlwaysAutoResize);
    if(ImGui::Button("Fire Particle")) {
        SNParticle p(1);
        p.pos = ImVec2(200, 120);
        LOG("Add particle!!");
        _pSystem.addParticle(p);
    }
    ImGui::End();
//    ImGui::ShowDemoWindow(&flag);
//
//    // A new window
//    ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.
//
//    ImGui::Text("This is some useful text.");   // Label inside the window
//
//    ImGui::End();
    
    //
    
}

void SampleParticleApp::handleInput(double deltaTime)
{

    if (getInputKey(SDLK_a)) {
        
        LOG("a key is pressed");
        
        //SNParticle p(1);
        //p.pos = ImVec2(120, 120);
        
        //_pSystem.addParticle(p);
    }
//    if (getInputKey(SDLK_w)) dir.y -= 1;
//    if (getInputKey(SDLK_s)) dir.y += 1;
//    if (getInputKey(SDLK_a)) dir.x -= 1;
//    if (getInputKey(SDLK_d)) dir.x += 1;
}
