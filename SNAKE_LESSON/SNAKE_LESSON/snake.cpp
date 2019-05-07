#include "snake.h"
#include <cassert>
#include <iostream>

extern const int BLOCK_SIZE;
extern const sf::Vector2u WINDOW_SIZES;
extern const sf::Vector2i WORLD_SIZES;


void Snake::Create(const sf::Vector2i& head_position)
{
    direction_ = None;

    Segment head = {
        head_position,
        sf::RectangleShape(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE)),
        sf::Color::Green
    };

    body_.push_back(std::move(head));
}


void Snake::RespawnSnake()
{
    body_.clear();
    Create(sf::Vector2i(WORLD_SIZES.x / 2, WORLD_SIZES.y / 2));
}


void Snake::Render(sf::RenderWindow& window)
{
    for (Segment& segment : body_)
    {
        segment.shape.setFillColor(segment.color);
        segment.shape.setSize(sf::Vector2f(BLOCK_SIZE - 1, BLOCK_SIZE - 1));
        segment.shape.setPosition(
            sf::Vector2f(
                BLOCK_SIZE * segment.position.x,
                BLOCK_SIZE * segment.position.y)
        );
        window.draw(segment.shape);
    }
}


bool Snake::CheckSelfCollision() const
{
    for (size_t i = 1; i < body_.size(); i++)
    {
        if (body_[i].position == body_[0].position)
        {
            return 1;
        }
    }
    return 0;
}


sf::Vector2i Snake::GetHeadPosition() const
{
    assert(!body_.empty());
    return body_[0].position;
}


const std::vector<Snake::Segment>& Snake::GetBody() const
{
    return body_;
}


void Snake::Update(const float dt)
{
    MoveByOneCell();
}


void Snake::MoveByOneCell()
{         
    for (int i = body_.size() - 1; i > 0; i--)
    {
        body_[i].position = body_[i - 1].position;
    }
    
    if (direction_ == Up)
    {
        body_[0].position.y -= 1;
    }
    else if (direction_ == Right)
    {
        body_[0].position.x += 1;
    }
    else if (direction_ == Down)
    {
        body_[0].position.y += 1;
    }
    else if (direction_ == Left)
    {
        body_[0].position.x -= 1;
    }
    const sf::Vector2f new_position(
        (float)body_[0].position.x,
        (float)body_[0].position.y
    );
    body_[0].shape.setPosition(new_position);
}


void Snake::Grow()
{
    assert(!body_.empty());
    if (body_.size() == 1)
    {
        sf::Vector2i new_position;
        if (direction_ == Up)
        {
            new_position = body_[0].position + sf::Vector2i(0, 1);
        }
        if (direction_ == Down)
        {
            new_position = body_[0].position + sf::Vector2i(0, -1);
        }
        if (direction_ == Right)
        {
            new_position = body_[0].position + sf::Vector2i(-1, 0);
        }
        if (direction_ == Left)
        {
            new_position = body_[0].position + sf::Vector2i(1, 0);
        }

        Segment new_part = {
            new_position,
            sf::RectangleShape(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE)),
            sf::Color::Yellow
        };
        new_part.shape.setPosition(
            (float)new_part.position.x, (float)new_part.position.y
        );
        new_part.shape.setFillColor(new_part.color);

        body_.push_back(std::move(new_part));   
    }
    else
    {
        sf::Vector2i new_position = body_.back().position;
        Segment new_part = {
            new_position,
            sf::RectangleShape(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE)),
            sf::Color::Yellow
        };
        new_part.shape.setPosition(
            (float)new_part.position.x, (float)new_part.position.y
        );
        new_part.shape.setFillColor(new_part.color);

        body_.push_back(std::move(new_part));
    }
}


void Snake::SetDirection(const Direction new_direction)
{
    direction_ = new_direction;
}


Snake::Direction Snake::GetDirection() const
{
    return direction_;
}


int Snake::GetScore() const
{
    return score_;
}


int Snake::GetLives() const
{
    return lives_;
}


void Snake::DecreaseLivesByOne()
{
    lives_ -= 1;
}


void Snake::IncreaseScore(const int delta_score)
{
    score_ += delta_score;
}