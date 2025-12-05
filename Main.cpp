#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Body.h"

int main()
{
    glfwInit();
    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);
    const GLFWvidmode* mode = glfwGetVideoMode(monitors[1]);
    GLFWwindow* window;
    window = glfwCreateWindow(mode->width, mode->height, "Orbit", monitors[1], nullptr);
    glfwMakeContextCurrent(window);

    glewInit();

    Body body({ 0, 0 }, 1, 1);
    glm::mat4 view = glm::scale(glm::mat4(1), { float(mode->height) / float(mode->width), 1, 1 });

    while(!glfwWindowShouldClose(window))
    {
        body.Render(view);
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    glfwDestroyWindow(window);
}