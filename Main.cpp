#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Body.h"

int main()
{
    GLFWwindow* window;
    glfwInit();
    window = glfwCreateWindow(1536, 1536, "Orbit", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glewInit();
    Body body({ 0, 0 }, 0.125, 1);

    while(!glfwWindowShouldClose(window))
    {
        body.Render();
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    glfwDestroyWindow(window);
}