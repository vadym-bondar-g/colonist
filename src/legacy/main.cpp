#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char* vertexShaderSource = R"(
#version 330 core 
layout(location = 0) in vec3 aPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)";
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main(){
    FragColor = vec4(0.6, 0.2, 0.8, 1.0);
}
)";


GLuint compileShader(GLenum type,const char* source){
GLuint shader = glCreateShader(type);

 glShaderSource(shader, 1, &source, nullptr);
 glCompileShader(shader);
 int success;
 char infoLog[512];
 glGetShaderiv(shader, GL_COMPILE_STATUS,&success);
    if(!success){
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    std::cout << "Shader compilation error:"<< infoLog<< "\n";    
    }
    return shader;
}

int main(){

if(!glfwInit()){std::cerr << "Failed initialize GLFW!\n";
return-1;}

glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
//
GLFWwindow* window = glfwCreateWindow(1000,800,"The Colonist", nullptr,nullptr);
if(!window){
std::cerr<< "Error create window!\n";
glfwTerminate();
return -1;}

glfwMakeContextCurrent(window);

    glewExperimental =GL_TRUE;
    if(glewInit() != GLEW_OK){std::cerr<< "Failed to initialize GLEW!\n";
    glfwTerminate();
    return -1;}
//
float vertices[]= {
    -0.5f,-0.5f,-0.5f,  0.5f,-0.5f,-0.5f,   0.5f,0.5f,-0.5f,  -0.5f,0.5f,-0.5f,
    -0.5f,-0.5f,0.5f, 0.5f,-0.5f,0.5f, 0.5f,0.5f,0.5f,  -0.5f,0.5f,0.5f     };
unsigned int indices[] = {
 0,1,2, 2,3,0,
 4,5,6, 6,7,4,
 0,1,5, 5,4,0,
 2,3,7, 7,6,2,
 1,2,6, 6,5,1,
 0,3,7, 7,4,0 };
GLuint VBO, VAO, EBO;
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glGenBuffers(1, &EBO);

glBindVertexArray(VAO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,GL_STATIC_DRAW);


glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
glEnableVertexAttribArray(0);//
glBindVertexArray(0);

GLuint vertexShader= compileShader(GL_VERTEX_SHADER,vertexShaderSource);
GLuint fragmentShader= compileShader(GL_FRAGMENT_SHADER,fragmentShaderSource);
GLuint shaderProgram= glCreateProgram();
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glLinkProgram(shaderProgram);
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);

glEnable(GL_DEPTH_TEST);

glm::mat4 projection = glm::perspective (glm::radians(45.0f),1000.0f/800.0f,0.1f,100.0f);
glm::mat4 view = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,-3));
while(!glfwWindowShouldClose(window)){

    glfwPollEvents();

    glClearColor(0.1f,0.2f,0.3f,1.0f);


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.5f,1.0f,0.0f));
    GLuint modelLoc =glGetUniformLocation(shaderProgram, "model");
    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLuint projLoc = glGetUniformLocation(shaderProgram, "projection");

    glUseProgram(shaderProgram);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36,GL_UNSIGNED_INT,0);
    glfwSwapBuffers(window);
}  
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
 
    glfwDestroyWindow(window);
    glfwTerminate();

return 0;}






