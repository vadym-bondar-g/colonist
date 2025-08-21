
#include <GL/glew.h>
#include "Window.h"
#include <stdexcept> 



Window::Window(int width, int height, const std::string& title, bool fullscreen ):m_Width(width), m_Height(height),m_Title(title){
    if(!glfwInit()) throw std::runtime_error("Failed to init GLFW");
 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
 glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /*m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if(!m_window){
        glfwTerminate();
        throw std::runtime_error("Failed to create Window");
     }   
    glfwMakeContextCurrent(m_window);
     
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
    throw std::runtime_error("Failed to init GLEW");
}*/

 GLFWmonitor* monitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;
 const GLFWvidmode* mode = fullscreen ?glfwGetVideoMode(monitor): nullptr;
m_window = glfwCreateWindow(fullscreen ? mode->width : m_Width,
 fullscreen ? mode->height : m_Height, 
 m_Title.c_str(), monitor, nullptr);
if (!m_window){glfwTerminate();
throw std::runtime_error("Window creation failed");
}
glfwMakeContextCurrent(m_window);   // glViewport(0, 0, width, height); - obsolete



}
Window::~Window(){
    glfwDestroyWindow(m_window);
    glfwTerminate();
}
void Window::Update(){ 
glfwSwapBuffers(m_window);
glfwPollEvents();}


bool Window::shouldClose() const {
return glfwWindowShouldClose(m_window);}
void Window::pollEvents() const{
    glfwPollEvents();}
void Window::swapBuffers() const{
    glfwSwapBuffers(m_window);
}
GLFWwindow* Window::GetNativeWindow() const{
    return m_window;
}
/*
void Window::clear() const{
glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
*/

