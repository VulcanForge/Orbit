#include <iostream>
#include <vector>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Body.h"
#include "Universe.h"

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

    bodies.emplace_back(glm::vec2 { -0.5 * mode->width / mode->height, 0 }, glm::vec2 { 0, 1.f / 8 }, 1.f / 64, 0);
    bodies.emplace_back(glm::vec2 { 0, 0 }, glm::vec2{ 0, 0 }, 1.f / 16, 1.f / 64);
    glm::mat4 view = glm::scale(glm::mat4(1), { float(mode->height) / float(mode->width), 1, 1 });

    float lastTime = glfwGetTime();
    float startTime = lastTime;
    float maxFrameTime = 0;
    unsigned int numberFrames = 0;

    while(!glfwWindowShouldClose(window))
    {
        float thisTime = glfwGetTime();
        float elapsed = thisTime - lastTime;
        maxFrameTime = fmaxf(elapsed, maxFrameTime);
        ++numberFrames;
        lastTime = thisTime;
        UpdateBodies(elapsed);

        glClear(GL_COLOR_BUFFER_BIT);
        RenderBodies(view);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << "Max frame time: " << maxFrameTime << "\n";
    std::cout << "Average frame time: " << (lastTime - startTime) / numberFrames << "\n";
}