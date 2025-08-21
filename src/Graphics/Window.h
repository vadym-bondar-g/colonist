#pragma once
#include <GLFW/glfw3.h>
#include <string>


class Window {
    public:
    Window(int width, int height, const std::string& title, bool fullscreen);
    ~Window();
   
 void Update();//added 21.09
    GLFWwindow* GetNativeWindow() const;// added
    bool shouldClose() const;
int GetWidth() const{return m_Width;}
int GetHeight() const {return m_Height;}
// 
    void pollEvents() const;
    void swapBuffers() const;
 // obsolete   void clear() const;

private: 
    GLFWwindow* m_window;
// last was added 21.09  
  int m_Width = 0, m_Height = 0;
    std::string m_Title;
};
