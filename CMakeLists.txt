cmake_minimum_required(VERSION 3.10)
project(colonist)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

find_package(glfw3 QUIET)
if (NOT glfw3_FOUND)
    find_package(GLFW3 REQUIRED)
endif()

include_directories(
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLIDE_DIR}
    ${GLM_INCLUDE_DIR}
)

file(GLOB_RECURSE SOURCES source/*.cpp)
add_executable(colonist src/Game/Main.cpp
                        src/Core/Application.cpp
                        src/Graphics/Window.cpp
                       src/Input/Input.cpp
                       src/World/WorldManager.cpp)
target_link_libraries(colonist PRIVATE OpenGL::GL GLEW::GLEW glfw glm::glm )
target_include_directories(colonist PRIVATE ${CMAKE_SOURCE_DIR}/external/tinyobjloader)

