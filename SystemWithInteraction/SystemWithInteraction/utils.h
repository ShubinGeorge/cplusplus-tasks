#pragma once
#include "partical_system.h"
#include "SFML/Graphics.hpp"

namespace utils
{

float ComputeLenght(const sf::Vector2f vector);
float GetAngleBetweenParticle(const Particle& particle1, const Particle& particle2);

} // namespace utils