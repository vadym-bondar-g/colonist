#pragma once
#include "../Graphics/Window.h"
#include "../Input/Input.h"
class Application{
    public:
        Application(int width, int height, const char* title, bool fullscreen= true);
        ~Application();
        void run();
//upd 21.09
        void Update();
    void Render();
    void ProcessInput();
    void UpdateDeltaTime();
    
private:    
    Window* m_window = nullptr;
    float m_DeltaTime;
    double m_LastTime;


};
