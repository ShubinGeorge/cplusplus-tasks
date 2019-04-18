#pragma once
#include <SFML/Graphics.hpp>

class Particle
{
    friend class ParticleSystem;
public:
    Particle(const sf::Vector2f position_, 
        const sf::Vector2f velocity_,
        const sf::Vector2f acceleration_,
        const float radius_, const float mass);
    virtual ~Particle() = default;

    void Push(const sf::Vector2f increment);
    void Update(const float dt);
    void Render(sf::RenderWindow& window);

    const sf::Vector2f& GetPosition() const;

private:
    sf::Vector2f position_;
    sf::Vector2f velocity_;
    sf::Vector2f acceleration_;
    float radius_;
    sf::Color color_;
    sf::CircleShape shape_;
    float mass_;
};


class ParticleSystem
{
    friend class Particle;
public:
    ParticleSystem() = default;
    virtual ~ParticleSystem() = default;

    using ParticleID = size_t;

    ParticleID AddParticle(
        sf::Vector2f position,
        sf::Vector2f velocity,
        sf::Vector2f acceleration,
        float radius,
        float mass);

    void AddLink(const ParticleID particle1_id,
        const ParticleID particle2_id,
        const float stiffness
    );

    const Particle& GetParticleByID(const ParticleID particle_id) const;

    void Push(const sf::Vector2f delta_velocity);
    void Update(const float dt);
    void Render(sf::RenderWindow& window);

    float ComputeDistanceBetween(const ParticleID patricle1_id, const ParticleID particle2_id) const;

private:
    void ApplyGravity();
    void HandleCollisons();
    void SolveLinks();
    struct Link
    {
        ParticleID particle1_id;
        ParticleID particle2_id;
        float stiffness;
        float initial_length;
    };

    std::vector<Particle> particles_;
    std::vector<Link> links_;
};