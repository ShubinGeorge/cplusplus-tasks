#include "world.h"
#include <iostream>

extern const int BLOCK_SIZE;
extern const sf::Vector2u WINDOW_SIZES;
extern const sf::Vector2i WORLD_SIZES;



void World::Create()
{
    Wall top_wall;
    top_wall.Create({ 0, 0 }, { WORLD_SIZES.x, 1 });
    walls_.push_back(top_wall);

    Wall left_wall;
    left_wall.Create({ 0, 0 }, { 1, WORLD_SIZES.y });
    walls_.push_back(std::move(left_wall));

    Wall right_wall;
    right_wall.Create({ WORLD_SIZES.x - 1, 0 }, {WORLD_SIZES.x, WORLD_SIZES.y });
    walls_.push_back(std::move(right_wall));
    /*
    Wall down_wall;
    down_wall.Create({0, WORLD_SIZES.y - 1}, {WORLD_SIZES.x, WORLD_SIZES.y});
    walls_.push_back(down_wall);
    */


    //message_box_.Create({ 0, WORLD_SIZES.y }, { WORLD_SIZES.x, 5 }, 5);

    snake_.Create(FindRandomFreeCell());
    apple_.Create(FindRandomFreeCell());
}


void World::Update(const float dt)
{

    snake_.Update(dt);
    apple_.Update(dt);
    //message_box_.Update(dt);

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
    //message_box_.Render(window);
    for (Wall& wall : walls_)
    {
        wall.Render(window);
    }
}



void World::HandleCollisions()
{
    if (snake_.CheckSelfCollision())
    {
        std::cout << "Self-crashed" << " lives = " << snake_.GetLives() << "\n";
        snake_.DecreaseLivesByOne();
        snake_.RespawnSnake();
    }

    for (const Wall& wall : walls_)
    {
        if (wall.CheckCellInWall(snake_.GetHeadPosition()))
        {
            snake_.DecreaseLivesByOne();
            std::cout << "Wall-crashed" << " lives = " << snake_.GetLives() << "\n";
            snake_.RespawnSnake();
            break;         
        }
    }

    if (snake_.GetLives() == 0)
    {
        exit(0);
    }

    if (snake_.GetHeadPosition() == apple_.GetPosition())
    {
        snake_.Grow();
        std::cout << "CRASHED" << "\n";
        apple_.Create(FindRandomFreeCell());
    }

}


sf::Vector2i World::FindRandomFreeCell() const
{
    while (true)
    {
        const sf::Vector2i random_cell_position(
            std::rand() % WORLD_SIZES.x,
            std::rand() % WORLD_SIZES.y
        );
        
        for (const Wall& wall : walls_)
        {
            if (!wall.CheckCellInWall(random_cell_position))
            {
                continue;
            }
        }

        if (random_cell_position == apple_.GetPosition())
        {
            continue;
        }

        for (const auto& snake_segment : snake_.GetBody())
        {
            if (random_cell_position == snake_segment.position)
            {
                continue;
            }
        }
        return random_cell_position;
    }
}

