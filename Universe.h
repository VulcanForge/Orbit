#pragma once

#include <vector>

#include <glm/mat4x4.hpp>

#include "Body.h"

extern std::vector<Body> bodies;

void UpdateBodies(float elapsed);
void RenderBodies(glm::mat4 view);
