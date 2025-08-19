#pragma once
#include <GLFW/glfw3.h>
#include <string>


class Window {
    public:
    Window(int width, int height, const std::string& title);
    ~Window();

    bool shouldClose() const;
    void pollEvents() const;
    void swapBuffers() const;
    void clear() const;
private: 
GLFWwindow* m_window;

};
