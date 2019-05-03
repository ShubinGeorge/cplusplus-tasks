#include "game.h"

#include <iostream>

extern const sf::Vector2u WINDOW_SIZES(800, 600);
extern const sf::Vector2i WORLD_SIZES(40, 30);
extern const int BLOCK_SIZE = 20;

Game::Game()
    : main_window_("Snake", WINDOW_SIZES)
{
    std::srand(static_cast <unsigned int>(std::time(nullptr)));//чтобы генерить разные рандомные числа
    world_.Create();
}


void Game::Run()
{
    const float updatets_per_seconds = 6.0f;
    const sf::Time time_per_update = sf::seconds(1.0f / updatets_per_seconds);

    sf::Clock clock;
    sf::Time time_since_last_update = sf::Time::Zero;

    while (!main_window_.CheckIsDone())
    {
        time_since_last_update += clock.restart();

        while (time_since_last_update >= time_per_update)
        {
            HandleInput();
            Update(time_per_update.asSeconds());
            time_since_last_update -= time_per_update;
        }
        
        Render();
    }
}


void Game::HandleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && world_.snake_.GetDirection() != Snake::Direction::Down)
    {
        world_.snake_.SetDirection(Snake::Direction::Up);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && world_.snake_.GetDirection() != Snake::Direction::Left)
    {
        world_.snake_.SetDirection(Snake::Direction::Right);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && world_.snake_.GetDirection() != Snake::Direction::Up)
    {
        world_.snake_.SetDirection(Snake::Direction::Down);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && world_.snake_.GetDirection() != Snake::Direction::Right)
    {
        world_.snake_.SetDirection(Snake::Direction::Left);
    }

}


void Game::Update(const float dt)
{
    main_window_.Update(dt);
    world_.Update(dt);
}


void Game::Render()
{
    main_window_.BeginDraw();

    world_.Render(main_window_.GetWindow());

    main_window_.EndDraw();
}