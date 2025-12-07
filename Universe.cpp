#include <vector>

#include <glm/mat4x4.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>

#include "Body.h"

std::vector<Body> bodies;

void UpdateBodies(float elapsed)
{
    for(auto actedOnBody = bodies.begin(); actedOnBody != bodies.end(); ++actedOnBody)
    {
        for(auto actingBody = bodies.cbegin(); actingBody != bodies.cend(); ++actingBody)
        {
            if(actedOnBody == actingBody)
                continue;

            float distanceSquared = glm::distance2(actedOnBody->position, actingBody->position);
            float gravity = actingBody->mass / distanceSquared;
            glm::vec2 direction = actingBody->position - actedOnBody->position;
            actedOnBody->velocity += elapsed * gravity * direction;
        }
    }

    for(auto actedOnBody = bodies.begin(); actedOnBody != bodies.end(); ++actedOnBody)
        actedOnBody->Update(elapsed);
}

void RenderBodies(glm::mat4 view)
{
    for(auto actedOnBody = bodies.begin(); actedOnBody != bodies.end(); ++actedOnBody)
        actedOnBody->Render(view);
}