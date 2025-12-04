#pragma once

#include <vector>

#include <glm/vec2.hpp>

class Body
{
private:
    std::vector<glm::vec2> vertices;
    unsigned int vao, vbo, ebo;

public:
    glm::vec2 position;
    float radius;
    float mass;

    Body(glm::vec2 position, float radius, float mass);

    void Render();
};