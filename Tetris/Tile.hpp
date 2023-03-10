#pragma once
#include "Engine.hpp"

class Tile : public GameObject
{
public:
    int row;
    int column;

    void moveDown()
    {
        getTransform()->position.y += getTransform()->scale.y;
        row += 1;
    }

    void moveUp()
    {
        getTransform()->position.y -= getTransform()->scale.y;
        row += 1;
    }
};