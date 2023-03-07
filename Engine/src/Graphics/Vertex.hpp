#pragma once

#ifdef _WIN32
#include "glm.hpp"
#else
#include "glm/glm.hpp"
#endif

struct Vertex
{
    glm::vec4 color;
    glm::vec2 position;
    glm::vec2 texCoord;

    Vertex(glm::vec2 positionParam, glm::vec2 texCoordParam, glm::vec4 colorParam)
    {
        position = positionParam;
        texCoord = texCoordParam;
        color = colorParam;
    }
};