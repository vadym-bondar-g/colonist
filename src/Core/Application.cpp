#include "Application.h"

void Application::run(){
    Window window(1280, 720, "The Colonist");

    while(!window.shouldClose()){

    window.clear();

    window.swapBuffers();
    window.pollEvents();
}
}
