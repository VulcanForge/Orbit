#include <iostream>
#include <vector>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Body.h"

int main()
{
    if(!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW.\n";
        return EXIT_FAILURE;
    }

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    GLFWwindow* window;
    window = glfwCreateWindow(mode->width, mode->height, "Orbit", monitor, nullptr);

    if(!window)
    {
        std::cerr << "Failed to create window.\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW.\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    Body body({ -float(mode->width) / float(mode->height), 0 }, { 0.0625, 0 }, 0.0625, 1);
    glm::mat4 view = glm::scale(glm::mat4(1), { float(mode->height) / float(mode->width), 1, 1 });

    float lastTime = glfwGetTime();
    glfwSwapInterval(1);

    while(!glfwWindowShouldClose(window))
    {
        float thisTime = glfwGetTime();
        float elapsed = thisTime - lastTime;
        lastTime = thisTime;
        body.Update(elapsed);

        glClear(GL_COLOR_BUFFER_BIT);
        body.Render(view);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}