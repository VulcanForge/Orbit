#include <iostream>

#include <gl/glew.h>

#include <GLFW/glfw3.h>

#include <ShaderProgram.h>

GLuint vao, vbo, ebo;
GLfloat vertices[]{ 0, 0, 1, 0, 0, 1, -1, 0, 0, -1 };
GLuint elements[]{ 0, 1, 2, 3, 4, 1 };

void InitializeBody()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), elements, GL_STATIC_DRAW);

}

int main()
{
    GLFWwindow* window;
    glfwInit();
    window = glfwCreateWindow(1920, 1080, "Orbit", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glewInit();
    InitializeBody();
    auto shader = ShaderProgram::CreateBasicShaderProgramWithNames("Body", "Shaders/Body.vert", "Shaders/Body.frag");

    while(!glfwWindowShouldClose(window))
    {
        shader->UseProgram();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    glfwDestroyWindow(window);
}