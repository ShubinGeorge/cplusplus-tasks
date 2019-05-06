#include "wall.h"
#include <cassert>
#include <iostream>
extern const int BLOCK_SIZE;


void Wall::Update(const float dt)
{
}


void Wall::Create(const sf::Vector2i& top_left, const sf::Vector2i& bottom_right)
{
    assert(top_left.x <= bottom_right.x);
    assert(top_left.y <= bottom_right.y);

    top_left_ = top_left;
    bottom_right_ = bottom_right;
}


void Wall::Render(sf::RenderWindow& window)
{
    shape_.setPosition({(float)top_left_.x * BLOCK_SIZE, (float)top_left_.y * BLOCK_SIZE});
    shape_.setSize(
        {(float)((bottom_right_.x + 1 - top_left_.x) * BLOCK_SIZE),
        (float)((bottom_right_.y + 1 - top_left_.y) * BLOCK_SIZE)}
    );
    shape_.setFillColor(sf::Color::Magenta);

    window.draw(shape_);
}


bool Wall::CheckCellInWall(const sf::Vector2i& cell) const
{
    if (top_left_.x <= cell.x && cell.x <= bottom_right_.x &&
            top_left_.y <= cell.y && cell.y <= bottom_right_.y)
    {
        return true;
    }
    return false;
}