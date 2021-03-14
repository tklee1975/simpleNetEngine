//
//  SNBaseImageApp.cpp
//
//  Created by kenlee on 6/3/2021.
//

#include "BaseImguiApp.h"
#include <stdio.h>
#include <iostream>
#include <fmt/core.h>

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>


#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h> // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h> // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h> // Initialize with gladLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
#include <glad/gl.h> // Initialize with gladLoadGL(...) or gladLoaderLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
#define GLFW_INCLUDE_NONE      // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/Binding.h> // Initialize with glbinding::Binding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
#define GLFW_INCLUDE_NONE        // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/glbinding.h> // Initialize with glbinding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

namespace simpleNet {

const char *glsl_version = "#version 150";

bool show_demo_window = false;
bool show_another_window = false;


BaseImguiApp::BaseImguiApp()
{
    _clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

BaseImguiApp::~BaseImguiApp()
{

}

// void update(SDL_Window *window, bool &_running);
//     void render(SDL_Window *window);
void BaseImguiApp::doUpdate()
{
    // // Poll and handle events (inputs, window resize, etc.)
    // // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
    // // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
    // // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
        {
            stopRun();
            return;
        }
    
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(_window))
        {
            stopRun();
            return;
        }
    
        // Core Rendering Logic
        //_owner->onEvent(event);
        onEvent(event);
    }
    
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(_window);
    ImGui::NewFrame();
    
    onUpdate(ImGui::GetIO().DeltaTime);
}

//void BaseImguiApp::render(SDL_Window *window)
void BaseImguiApp::doRender()
{
    // // Rendering
    ImGui::Render();
    
    ImGuiIO &io = ImGui::GetIO();
    
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(_clearColor.x * _clearColor.w, _clearColor.y * _clearColor.w,
                 _clearColor.z * _clearColor.w, _clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT);

    // Core Rendering Logic
    onRender();

    // 
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(_window);
}

void BaseImguiApp::onUpdate(double delta)
{
    
}

void BaseImguiApp::onInit()
{
    
}

bool BaseImguiApp::init()
{
    _hasInit = false;
    
    if(initWindow() == false) {
        return false;
    }
    
    if(initGLContext() == false) {
        return false;
    }
    
    onInit();
    
    initImgui();
    
    _hasInit = true;
    
    return true;
}

bool BaseImguiApp::initGLContext()
{
    if (_window == nullptr)
    {
        std::cout << "initGLContext: window isn't init\n";
        return false;
    }
    
    
    _glContext = SDL_GL_CreateContext(_window);
    SDL_GL_MakeCurrent(_window, _glContext);
    SDL_GL_SetSwapInterval(1); // Enable vsync
    
    // Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    bool err = gladLoadGL() == 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
    bool err = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress) == 0; // glad2 recommend using the windowing library loader instead of the (optionally) bundled one.
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
    bool err = false;
    glbinding::Binding::initialize();
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
    bool err = false;
    glbinding::initialize([](const char *name) { return (glbinding::ProcAddress)SDL_GL_GetProcAddress(name); });
#else
    bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
    if (err)
    {
        std::cout << "Failed to initialize OpenGL loader!";
        return 0;
    }
    
    
    return true;
}


bool BaseImguiApp::initWindow() 
{
    int error = SDL_Init(SDL_INIT_EVERYTHING);
    if (error != 0)
    {
        std::cout << "Fail init. code=" << error << "\n";
        return 0;
    }
    
    
    
    //
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    
    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(
                                                     SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    
    _window = SDL_CreateWindow("Dear ImGui SDL2+OpenGL3 example",
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               720, 720, window_flags);    // KEN: Win Size
    
    if (_window == nullptr)
    {
        std::cout << "Fail to create window\n";
        return false;
    }
    
    return true;
}


void BaseImguiApp::initImgui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(_window, _glContext);
    ImGui_ImplOpenGL3_Init(glsl_version);
    
}

void BaseImguiApp::onEvent(SDL_Event &event)
{
    
}

void BaseImguiApp::onRender()
{
//    ImVec4 topColor = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
//        ImVec4 leftColor = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
//        ImVec4 rightColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    
    // rendering our geometries
            //triangle_shader.use();
            // glBindVertexArray(vao);
//            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
//            glBindVertexArray(0);


}


void BaseImguiApp::stopRun()
{
    _running = false;
}

void BaseImguiApp::run()
{
    if(_hasInit == false) {
        std::cout << "ImGui not yet initialized\n";
        return;
    }
    
    _running = true;
    while (_running)
    {
        doUpdate();
        doRender();
    }
}

bool BaseImguiApp::getInputKey(SDL_Keycode key)
{
    auto s = SDL_GetScancodeFromKey(key);
    return ImGui::GetIO().KeysDown[s];
}


// int main()
// {
//     SDL_Window *window = nullptr;
//     SDL_GLContext gl_context = nullptr;
//     // std::cout << "testing" << "\n'";
//     // for(int i=0; i<20; i++) {
//     //     fmt::print("i={}\n", i);
//     // }

//     int error = SDL_Init(SDL_INIT_EVERYTHING);
//     if (error != 0)
//     {
//         std::cout << "Fail init. code=" << error << "\n";
//         return 0;
//     }

//     // Decide GL+GLSL versions
//     const char *glsl_version = "#version 150";
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

//     // Create window with graphics context
//     SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
//     SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
//     SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

//     SDL_WindowFlags window_flags = (SDL_WindowFlags)(
//         SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
//     window = SDL_CreateWindow("Dear ImGui SDL2+OpenGL3 example",
//                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720,
//                               window_flags);

//     if (window == nullptr)
//     {
//         std::cout << "Window is null!\n";
//         return 0;
//     }

//     gl_context = SDL_GL_CreateContext(window);
//     SDL_GL_MakeCurrent(window, gl_context);
//     SDL_GL_SetSwapInterval(1); // Enable vsync

//     // Initialize OpenGL loader
// #if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
//     bool err = gl3wInit() != 0;
// #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
//     bool err = glewInit() != GLEW_OK;
// #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
//     bool err = gladLoadGL() == 0;
// #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
//     bool err = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress) == 0; // glad2 recommend using the windowing library loader instead of the (optionally) bundled one.
// #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
//     bool err = false;
//     glbinding::Binding::initialize();
// #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
//     bool err = false;
//     glbinding::initialize([](const char *name) { return (glbinding::ProcAddress)SDL_GL_GetProcAddress(name); });
// #else
//     bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
// #endif
//     if (err)
//     {
//         std::cout << "Failed to initialize OpenGL loader!";
//         return 0;
//     }



//     IMGUI_CHECKVERSION();
//     ImGui::CreateContext();

//     // Setup Dear ImGui style
//     ImGui::StyleColorsDark();
//     //ImGui::StyleColorsClassic();

//     // Setup Platform/Renderer backends
//     std::cout << "Check 1\n";
//     ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
//     ImGui_ImplOpenGL3_Init(glsl_version);

//     std::cout << "Check 2\n";
//     // Update
//     bool _running = true;
//     while (_running)
//     {
//         _update(window, _running);
//         _render(window);
//     }
//     return 0;
// }
}

