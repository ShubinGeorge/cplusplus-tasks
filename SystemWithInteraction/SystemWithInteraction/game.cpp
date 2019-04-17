#include "game.h"

extern const sf::Vector2u WINDOW_SIZES(800, 600);

Game::Game()
    : main_window_("Particle_system", WINDOW_SIZES)
{
    ParticleSystem::ParticleID particle1_id = particles_.AddParticle(
        sf::Vector2f(100.0f, 100.0f), // position 
        sf::Vector2f(0, 0), // velocity 
        sf::Vector2f(0, 0), // acceleration 
        25.0f, // radius 
        15000.0f // mass 
    );
    
    ParticleSystem::ParticleID particle2_id = particles_.AddParticle(
        sf::Vector2f(100.0f, 400.0f), // position 
        sf::Vector2f(0, 0), // velocity 
        sf::Vector2f(0, 0), // acceleration 
        25.0f, // radius 
        15000.0f // mass 
    );
    
    ParticleSystem::ParticleID particle3_id = particles_.AddParticle(
        sf::Vector2f(400.0f, 100.0f), // position 
        sf::Vector2f(0, 0), // velocity 
        sf::Vector2f(0, 0), // acceleration 
        25.0f, // radius 
        15000.0f // mass 
    );
   
    ParticleSystem::ParticleID particle4_id = particles_.AddParticle(
        sf::Vector2f(400.0f, 400.0f), // position 
        sf::Vector2f(0, 0), // velocity 
        sf::Vector2f(0, 0), // acceleration 
        25.0f, // radius 
        15000.0f // mass 
    );
    
    particles_.AddLink(
        particle1_id, particle2_id,
        1e5 // stiffness 
    );
    
    particles_.AddLink(
        particle2_id, particle3_id,
        1e5 // stiffness 
    );
    
    particles_.AddLink(
        particle3_id, particle4_id,
        1e5 // stiffness 
    );
    
    particles_.AddLink(
        particle1_id, particle4_id,
        1e5 // stiffness 
    );
    
    particles_.AddLink(
        particle1_id, particle3_id,
        1e5 // stiffness 
    );
    
    particles_.AddLink(
        particle4_id, particle2_id,
        1e5 // stiffness 
    );
    
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

    particles_.Push(increment);
}


void Game::Update(const float dt)
{
    main_window_.Update(dt);
    particles_.Update(dt);
}


void Game::Render()
{
    main_window_.BeginDraw();
  
    particles_.Render(main_window_.GetWindow());
    
    main_window_.EndDraw();
}