#include "game.h"

extern const sf::Vector2u WINDOW_SIZES(800, 600);

Game::Game()
    : main_window_("Particle_system", WINDOW_SIZES)
{
    particles_.AddParticle(sf::Vector2f(WINDOW_SIZES.x / 3.0f, WINDOW_SIZES.y / 3.0f),
        sf::Vector2f(0, 0),
        sf::Vector2f(0, 15.0f),
        25.0f);

    particles_.AddParticle(sf::Vector2f(WINDOW_SIZES.x / 2.0f, WINDOW_SIZES.y / 2.0f),
        sf::Vector2f(0, 0),
        sf::Vector2f(0, 15.0f),
        50.0f);

    particles_.AddParticle(sf::Vector2f(WINDOW_SIZES.x / 5.0f, WINDOW_SIZES.y / 2.0f),
        sf::Vector2f(0, 0),
        sf::Vector2f(0, 15.0f),
        75.0f);
}



void Game::Run()
{
    const float updatets_per_seconds = 60.0f;
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
    sf::Vector2f increment(0, 0);
    const float delta = 100.0f;


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        increment.y -= delta;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        increment.x += delta;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        increment.y += delta;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        increment.x -= delta;
    }

    for (size_t i = 0; i < particles_.GetSize(); i++)
    {
        particles_.GetParticleByID(i).Push(increment);
    }
}

void Game::Update(const float dt)
{
    main_window_.Update(dt);
    for (size_t i = 0; i < particles_.GetSize(); i++)
    {
        particles_.GetParticleByID(i).Update(dt);
    }
}


void Game::Render()
{
    main_window_.BeginDraw();

    for (size_t i = 0; i < particles_.GetSize(); i++)
    {
        main_window_.Draw(particles_.GetParticleByID(i));
    }

    main_window_.EndDraw();
}


