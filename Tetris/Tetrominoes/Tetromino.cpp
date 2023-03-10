#include "Tetromino.hpp"

Tetromino::Tetromino(float tileScale)
{
    auto transform = addTransform();
    transform->setScale(glm::vec2(tileScale, tileScale));
    transform->setPosition(glm::vec2(tileScale * 3, 0));

    tiles = std::array<std::shared_ptr<Tile>, 4>();
    rotationState = 0;
}

void Tetromino::moveUp()
{
    auto transform = getTransform();
    transform->position.y -= transform->scale.x;
    for (auto& tile : tiles)
    {
        tile->moveUp();
    }
}

void Tetromino::moveDown()
{
    auto transform = getTransform();
    transform->position.y += transform->scale.x;
    for (auto& tile : tiles)
    {
        tile->moveDown();
    }
}

void Tetromino::moveLeft()
{
    auto transform = getTransform();
    transform->position.x -= transform->scale.x;
    for (auto tile : tiles)
    {
        auto tileTransform = tile->getTransform();
        tileTransform->position.x -= tileTransform->scale.x;
        tile->column--;
    }
}

void Tetromino::moveRight()
{
    auto transform = getTransform();
    transform->position.x += transform->scale.x;
    for (auto tile : tiles)
    {
        auto tileTransform = tile->getTransform();
        tileTransform->position.x += tileTransform->scale.x;
        tile->column++;
    }
}

void Tetromino::rotate()
{
    rotationState++;
    if (rotationState == 4)
    {
        rotationState = 0;
    }

    resolveRotations();

}

void Tetromino::undoRotation()
{
    rotationState--;
    if (rotationState < 0)
    {
        rotationState = 3;
    }

    resolveRotations();
}