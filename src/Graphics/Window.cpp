
#include <GL/glew.h>
#include "Window.h"
#include <stdexcept> 



Window::Window(int width, int height, const std::string& title){
    if(!glfwInit()) throw std::runtime_error("Failed to init GLFW");
 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
 glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if(!m_window){
        glfwTerminate();
        throw std::runtime_error("Failed to create Window");
     }   
    glfwMakeContextCurrent(m_window);
     
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
    throw std::runtime_error("Failed to init GLEW");
}

    glViewport(0, 0, width, height);


}
Window::~Window(){
    glfwDestroyWindow(m_window);
    glfwTerminate();
}
bool Window::shouldClose() const {
return glfwWindowShouldClose(m_window);}
void Window::pollEvents() const{
    glfwPollEvents();}
void Window::swapBuffers() const{
    glfwSwapBuffers(m_window);
}

void Window::clear() const{
glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


