#include "utils.h"
#include "partical_system.h"
#include <cmath>

#define PI 3.14159265 

namespace utils
{

float ComputeLenght(const sf::Vector2f vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

float GetAngleBetweenParticle(const Particle& particle1, const Particle& particle2)
{
    return 180 / PI * atan2(particle2.GetPosition().y - particle1.GetPosition().y,
            particle2.GetPosition().x - particle1.GetPosition().x);
}

}