#include "Body.h"

#include <numbers>
#include <vector>

#include <GL/glew.h>

#include <glm/vec2.hpp>

#include "ShaderProgram.h"

const int VERTEX_COUNT = 256;
std::vector<glm::vec2> defaultVertices;
unsigned int elements[VERTEX_COUNT + 2];
std::unique_ptr<ShaderProgram> shader;

void InitializeVertices()
{
    defaultVertices.emplace_back(0, 0);
    elements[0] = 0;

    for(int i = 0; i < VERTEX_COUNT; ++i)
    {
        float angle = (2 * i - VERTEX_COUNT) * std::numbers::pi / VERTEX_COUNT;
        float x = cos(angle);
        float y = sin(angle);
        defaultVertices.emplace_back(x, y);
        elements[i + 1] = i + 1;
    }

    elements[VERTEX_COUNT + 1] = 1;

    shader = ShaderProgram::CreateBasicShaderProgramWithNames("Body", "Shaders/Body.vert", "Shaders/Body.frag");
}

Body::Body(glm::vec2 position, float radius, float mass)
    : position(position), radius(radius), mass(mass)
{
    if(defaultVertices.empty())
        InitializeVertices();

    for(glm::vec2 vertex : defaultVertices)
        vertices.push_back(radius * vertex + position);

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
}

void Body::Render()
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLE_FAN, VERTEX_COUNT + 2, GL_UNSIGNED_INT, 0);
    shader->UseProgram();
}