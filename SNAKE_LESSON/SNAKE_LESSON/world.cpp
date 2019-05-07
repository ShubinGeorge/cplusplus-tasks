#include "world.h"
#include <iostream>

extern const int BLOCK_SIZE;
extern const sf::Vector2u WINDOW_SIZES;
extern const sf::Vector2i WORLD_SIZES;


void World::Create()
{
    Wall top_wall;
    top_wall.Create({ 0, 0 }, { WORLD_SIZES.x - 1, 0 });
    walls_.push_back(top_wall);

    Wall left_wall;
    left_wall.Create({ 0, 0 }, { 0, WORLD_SIZES.y - 1 });
    walls_.push_back(std::move(left_wall));

    Wall right_wall;
    right_wall.Create(
    { WORLD_SIZES.x - 1, 0 }, {WORLD_SIZES.x - 1, WORLD_SIZES.y - 1 }
    );
    walls_.push_back(std::move(right_wall));
    
    Wall down_wall;
    down_wall.Create(
    { 0, WORLD_SIZES.y - 1 }, { WORLD_SIZES.x - 1, WORLD_SIZES.y - 1 }
    );
    walls_.push_back(down_wall);
    
    events_ = Event::None;

    snake_.Create(FindRandomFreeCell());
    apple_.Create(FindRandomFreeCell());
}


void World::Update(const float dt)
{
    snake_.Update(dt);
    apple_.Update(dt);

    for (Wall& wall : walls_)
    {
        wall.Update(dt);
    }

    HandleCollisions();
}


void World::Render(sf::RenderWindow& window)
{
    snake_.Render(window);
    apple_.Render(window);

    for (Wall& wall : walls_)
    {
        wall.Render(window);
    }
}



void World::HandleCollisions()
{
    if (snake_.CheckSelfCollision())
    {
        snake_.DecreaseLivesByOne();
        snake_.RespawnSnake();
        events_  = Event::CollisionWithSnake;
    }

    for (const Wall& wall : walls_)
    {
        if (wall.CheckCellInWall(snake_.GetHeadPosition()))
        {
            snake_.DecreaseLivesByOne();
            snake_.RespawnSnake();
            events_ = Event::CollisionWithWall;
            break;         
        }
    }

    if (snake_.GetHeadPosition() == apple_.GetPosition())
    {
        snake_.Grow();
        snake_.IncreaseScore(1);
        apple_.Create(FindRandomFreeCell());
        events_ = Event::CollisionWithApple;
    }
}


World::Event World::GetLastEvent() const
{
    return events_;
}


void World::SetDirection(const Event new_event)
{
    events_ = new_event;
}


sf::Vector2i World::FindRandomFreeCell() const
{
    while (true)
    {
        bool is_random_cell_collided = false;
        const sf::Vector2i random_cell_position(
            std::rand() % WORLD_SIZES.x,
            std::rand() % WORLD_SIZES.y
        );

        // Check possible collisions with walls
        for (const Wall& wall : walls_)
        {
            if (wall.CheckCellInWall(random_cell_position))
            {
                is_random_cell_collided = true;
                break;
            }
        }

        // Check possible collisions with snake
        if (!is_random_cell_collided)
        {
            const auto& snake_body = snake_.GetBody();
            for (const auto& snake_segment : snake_body)
            {
                if (snake_segment.position == random_cell_position)
                {
                    is_random_cell_collided = true;
                    break;
                }
            }
        }

        // Check possible collision with apple
        if (!is_random_cell_collided)
        {
            if (apple_.GetPosition() == random_cell_position)
            {
                is_random_cell_collided = true;
            }
        }

        if (!is_random_cell_collided)
        {
            return random_cell_position;
        }
    }
}

