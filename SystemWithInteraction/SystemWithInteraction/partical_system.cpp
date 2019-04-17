#include "partical_system.h"
#include "utils.h"
#include <cmath>
#include <iostream>

extern const sf::Vector2u WINDOW_SIZES;
using ParticleID = size_t;


Particle::Particle(const sf::Vector2f position,const sf::Vector2f velocity,
    const sf::Vector2f acceleration, const float radius, const float mass)
    : position_(position)
    , velocity_(velocity)
    , acceleration_(acceleration)
    , radius_(radius)
    , mass_(mass)
{
    shape_.setRadius(radius);
    shape_.setFillColor(sf::Color::Yellow);
    shape_.setOrigin(sf::Vector2f(radius, radius));
    shape_.setPosition(position);
}


void Particle::Push(const sf::Vector2f delta_velocity)
{
    velocity_ += delta_velocity;
}


void Particle::Update(const float dt)
{
    velocity_ += acceleration_ * dt;
    position_ += velocity_ * dt;
    
}


const sf::Vector2f& Particle::GetPosition() const 
{
    return position_;
}


void Particle::Render(sf::RenderWindow& window)
{
    shape_.setPosition(position_);
    shape_.setRadius(radius_);
    window.draw(shape_);
}


ParticleID ParticleSystem::AddParticle(
    sf::Vector2f position, sf::Vector2f velocity,
    sf::Vector2f acceleration, float radius, float mass)
{
    Particle new_particle(position, velocity, acceleration, radius, mass);
    particles_.push_back(new_particle);
    return particles_.size() - 1;
}


void ParticleSystem::AddLink(const ParticleID particle1_id,
    const ParticleID particle2_id, const float stiffness)
{
    links_.push_back(Link{
        particle1_id, particle2_id,
        ComputeDistanceBetween(particle1_id, particle2_id),
        stiffness });
}


const Particle& ParticleSystem::GetParticleByID(const ParticleID particle_id) const
{
    return particles_[particle_id];
}


void ParticleSystem::Render(sf::RenderWindow& window)
{
    for (Link& link : links_)
    {
        const Particle& particle1 = GetParticleByID(link.particle1_id);
        const Particle& particle2 = GetParticleByID(link.particle2_id);

        const float min_distance = 2 * (particle1.radius_ + particle2.radius_);
        const float distance = ComputeDistanceBetween(link.particle1_id, link.particle2_id);

        const float max_width = std::min(particle1.radius_, particle2.radius_);
        const float width = distance > min_distance ? max_width * 100 / distance : max_width;

        const int intensity = distance > min_distance ? min_distance / distance * 255 : 255;

        sf::RectangleShape line(sf::Vector2f(distance, width));
        line.setPosition(particle1.GetPosition());
        line.setOrigin(0, particle1.radius_ / 2);
        line.setFillColor(sf::Color(intensity, 0 , 0));
        line.rotate(utils::GetAngleBetweenParticle(particle1, particle2));

        window.draw(line);
    }
    for (int i = 0; i < particles_.size(); i++)
    {
        particles_[i].Render(window);
    }

}


void ParticleSystem::Update(const float dt)
{
    for (Particle& particle : particles_)
    {
        particle.acceleration_ = sf::Vector2f(0.0f, 0.0f);
    }

    SolveLinks();
    ApplyGravity();

    for (Particle& particle : particles_)
    {
        particle.Update(dt);
    }

    HandleCollisons();
}


float ParticleSystem::ComputeDistanceBetween(const ParticleID particle1_id, const ParticleID particle2_id) const
{
    const Particle& particle1 = GetParticleByID(particle1_id);
    const Particle& particle2 = GetParticleByID(particle2_id);

    const sf::Vector2f distance_vector12 = particle1.position_ - particle2.position_;

    return utils::ComputeLenght(distance_vector12);
}


void ParticleSystem::Push(const sf::Vector2f delta_velocity)
{
    for (int i = 0; i < particles_.size(); i++)
    {
        particles_[i].Push(delta_velocity);
    }
}


const size_t ParticleSystem::GetSize() const
{
    return particles_.size();
}

void ParticleSystem::ApplyGravity()
{
    const sf::Vector2f acceleration_g(0.0f, 200.0f);
    for (Particle& particle : particles_)
    {
        particle.acceleration_ += acceleration_g;
    }
}

void ParticleSystem::HandleCollisons()
{
    for (Particle& particle : particles_)
    {
        if (particle.position_.x < particle.radius_)
        {
            particle.position_.x = particle.radius_;
            particle.velocity_.x = -particle.velocity_.x / 2.0f;
        }

        if (particle.position_.x + particle.radius_ > WINDOW_SIZES.x)
        {
            particle.position_.x = WINDOW_SIZES.x - particle.radius_;
            particle.velocity_.x = -particle.velocity_.x / 2.0f;
        }

        if (particle.position_.y < particle.radius_)
        {
            particle.position_.y = particle.radius_;
            particle.velocity_.y = -particle.velocity_.y / 2.0f;
        }

        const float bottom_gap = 50.0f;
        if (particle.position_.y + particle.radius_ + bottom_gap > WINDOW_SIZES.y)
        {
            particle.position_.y = WINDOW_SIZES.y - particle.radius_ - bottom_gap;
            particle.velocity_.y = -particle.velocity_.y / 2.0f;
        }
    }
}


void ParticleSystem::SolveLinks()
{
    for (Link& link : links_)
    {
        Particle& particle1 = particles_[link.particle1_id];
        Particle& particle2 = particles_[link.particle2_id];
        
        const sf::Vector2f distance_vector12 = (particle2.position_ - particle1.position_);
        const float distance = utils::ComputeLenght(distance_vector12);
        const float delta = distance - link.initial_length;
        const float force = link.stiffness * delta;
        const sf::Vector2f unit_vector12 = distance_vector12 / distance;
        particle1.acceleration_ += (force * unit_vector12) / particle1.mass_;
        particle2.acceleration_ -= (force * unit_vector12) / particle2.mass_;

        if (distance <= 2 * (particle1.radius_ + particle2.radius_))
        {
            particle1.velocity_ = sf::Vector2f(0.0, 0.0);
            particle2.velocity_ = sf::Vector2f(0.0, 0.0);
        }
    }
}
