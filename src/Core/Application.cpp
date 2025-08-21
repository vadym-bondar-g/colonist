
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Application.h"
#include <iostream>

Application::Application(int w, int h, const char* title, bool fullscreen){
    m_window = new Window(w, h, title, fullscreen);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Glew init failed");
        /* code */
    }
    glEnable(GL_DEPTH_TEST);
 

  Input::Init(m_window->GetNativeWindow());
  m_LastTime = glfwGetTime();
}


Application::~Application(){delete m_window;}
void Application::run(){

    while(!m_window->shouldClose()){
        UpdateDeltaTime();
        m_window->pollEvents();
        ProcessInput();
        Update();
        Render();
        
        m_window->swapBuffers();
    }
}

void Application::UpdateDeltaTime(){
double now= glfwGetTime();
m_DeltaTime= static_cast<float>(now - m_LastTime);
m_LastTime = now;

}
void Application::ProcessInput(){
if(Input::IsKeyPressed(GLFW_KEY_ESCAPE)){glfwSetWindowShouldClose(m_window->GetNativeWindow(),true);}
if(Input::IsKeyPressed(GLFW_KEY_W)){std::cout<< "Move forward (W)\n";}
if(Input::IsKeyPressed(GLFW_KEY_SPACE)){std::cout << "Jump (Space)\n";}
}
void Application::Update(){}



void Application::Render(){
glClearColor(0.08f,0.09f, 0.12f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



}
