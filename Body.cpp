#include "Body.h"

#include <cmath>
#include <memory>
#include <numbers>
#include <vector>

#include <GL/glew.h>

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "ShaderProgram.h"

const int VERTEX_COUNT = 256;
std::vector<glm::vec2> vertices;
GLuint elements[VERTEX_COUNT + 2];
GLuint vao, vbo, ebo;
std::unique_ptr<ShaderProgram> shader;

void InitializeGlobals()
{
    vertices.emplace_back(0, 0);
    elements[0] = 0;

    for(int i = 0; i < VERTEX_COUNT; ++i)
    {
        float angle = (2 * i - VERTEX_COUNT) * std::numbers::pi / VERTEX_COUNT;
        float x = cos(angle);
        float y = sin(angle);
        vertices.emplace_back(x, y);
        elements[i + 1] = i + 1;
    }

    elements[VERTEX_COUNT + 1] = 1;
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);
    glEnableVertexAttribArray(0);
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    shader = ShaderProgram::CreateBasicShaderProgramWithNames("Body", "Shaders/Body.vert", "Shaders/Body.frag");
}

Body::Body(glm::vec2 position, float radius, float mass)
    : position(position), radius(radius), mass(mass)
{
    if(vertices.empty())
        InitializeGlobals();    
}

void Body::Render(glm::mat4 view)
{
    glBindVertexArray(vao);
    shader->UseProgram();
    glm::mat4 transform = view * glm::translate(glm::scale(glm::mat4(1), { radius, radius, 1 }), glm::vec3(position, 0));
    shader->SetUniformMat4("transform", transform);
    glDrawElements(GL_TRIANGLE_FAN, VERTEX_COUNT + 2, GL_UNSIGNED_INT, 0);
}