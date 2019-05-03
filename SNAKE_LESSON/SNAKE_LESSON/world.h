#pragma once

#include "window.h"
#include "apple.h"
#include "snake.h"
#include "wall.h"
#include "message_box.h"

class World
{
    friend class Game;

public:
    World() = default;
    virtual ~World() = default;

    void Create();

    void Update(const float dt);
    void Render(sf::RenderWindow& window);

private:
    void HandleCollisions();//в конце метода Update
    sf::Vector2i FindRandomFreeCell() const;
    //MessageBox message_box_;
    Snake snake_;
    Apple apple_;
    std::vector<Wall> walls_;
};