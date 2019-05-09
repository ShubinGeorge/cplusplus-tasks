#pragma once

#include "window.h"
#include "apple.h"
#include "snake.h"
#include "wall.h"


class World
{
    friend class Game;

public:

    enum class Event
    {
        CollisionWithWall,
        CollisionWithSnake,
        CollisionWithApple,
        None
    };

    World() = default;
    virtual ~World() = default;

    void Create();

    void Update(const float dt);
    void Render(sf::RenderWindow& window);

    Event GetLastEvent() const;
    void SetDirection(const Event new_event);

private:
    void HandleCollisions();
    sf::Vector2i FindRandomFreeCell() const;
    Event events_;
    Snake snake_;
    Apple apple_;
    std::vector<Wall> walls_;
};