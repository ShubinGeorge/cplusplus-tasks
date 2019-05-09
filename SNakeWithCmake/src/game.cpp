#include "game.h"
#include <iostream>


extern const sf::Vector2u WINDOW_SIZES(800, 600);
extern const sf::Vector2i WORLD_SIZES(40, 20);
extern const int BLOCK_SIZE = 20;

Game::Game()
   : main_window_("Snake", WINDOW_SIZES),
     message_box_({0, (int)WORLD_SIZES.y * BLOCK_SIZE},
     { (int)WORLD_SIZES.x * BLOCK_SIZE,
       (int)WINDOW_SIZES.y - WORLD_SIZES.y * BLOCK_SIZE },
     50)
{
    std::srand(static_cast <unsigned int>(std::time(nullptr)));
    world_.Create();
}


void Game::Run()
{
    const float updatets_per_seconds = 10.0f;
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
        AddMessage();
        Render();

        if (world_.snake_.GetLives() == 0)
        {
            exit(0);
        }
    }
}


void Game::AddMessage()
{
    const std::string snake_score = std::to_string(world_.snake_.GetScore());
    const std::string snake_lives = std::to_string(world_.snake_.GetLives());
    message_box_.AddInTop("Game started: lives = " +
           snake_lives + " score = " + snake_score);

    if (world_.GetLastEvent() == World::Event::CollisionWithApple)
    {
        message_box_.Add("Apple eaten, score + 1");
        world_.SetDirection(World::Event::None);
    }

    if (world_.GetLastEvent() == World::Event::CollisionWithSnake)
    {
        message_box_.Add("Self-Collision, lives - 1");
        world_.SetDirection(World::Event::None);
    }

    for (const Wall& wall : world_.walls_)
    {
        if (world_.GetLastEvent() == World::Event::CollisionWithWall)
        {
            message_box_.Add("Wall-Collision, lives - 1");
            world_.SetDirection(World::Event::None);
        }
    }
}


void Game::HandleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
        world_.snake_.GetDirection() != Snake::Direction::Down)
    {
        world_.snake_.SetDirection(Snake::Direction::Up);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
        world_.snake_.GetDirection() != Snake::Direction::Left)
    {
        world_.snake_.SetDirection(Snake::Direction::Right);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
        world_.snake_.GetDirection() != Snake::Direction::Up)
    {
        world_.snake_.SetDirection(Snake::Direction::Down);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
        world_.snake_.GetDirection() != Snake::Direction::Right)
    {
        world_.snake_.SetDirection(Snake::Direction::Left);
    }
}


void Game::Update(const float dt)
{
    main_window_.Update(dt);
    message_box_.Update(dt);
    world_.Update(dt);
}


void Game::Render()
{
    main_window_.BeginDraw();

    world_.Render(main_window_.GetWindow());
    message_box_.Render(main_window_.GetWindow());

    main_window_.EndDraw();
}