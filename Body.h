#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

class Body
{
public:
    glm::vec2 position;
    float radius;
    float mass;

    Body(glm::vec2 position, float radius, float mass);

    void Render(glm::mat4 view);
};