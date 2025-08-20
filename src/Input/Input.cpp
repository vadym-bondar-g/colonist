#include "Input.h"

GLFWwindow* Input::s_Window = nullptrl;

void Input::Init(GLFWwindow* window){
    s_Window = window;
}
bool Input::IsKeyPressed(int key){
if(!s_Window)return false;
int state = glfwGetKey(s_Window,key);
return state == GLFW_PRESS || state == GLFW_REPEAT;
}// Проверка нажатой клавиши

bool Iput::IsMouseButtonPressed(int button){
if(!s_Window) return false;
    int state == glfwGetMouseButton(s_Window, button);
 
   return state == GLFW_PRESS;
}// Нажата ли клавиша мыши и какая 
void Input::GetMousePosition(double& x, double& y){
if(!s_Window){x = 0; y = 0; return;}
glfwGetCursorPos(s_Window, &x,&y);

}// Позиция мыши 
