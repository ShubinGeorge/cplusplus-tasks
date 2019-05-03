#include "apple.h"

extern const sf::Vector2i WORLD_SIZES;
extern const int BLOCK_SIZE;

void Apple::Create(sf::Vector2i& new_position)
{
    position_ = new_position;
    shape_.setRadius(BLOCK_SIZE / 2);
    shape_.setFillColor(sf::Color::Red); 
}


sf::Vector2i Apple::GetPosition() const
{
    return position_; 
}


void Apple::Update(const float dt)
{
    //
}


void Apple::Render(sf::RenderWindow& window)
{
    shape_.setPosition({(float)position_.x * BLOCK_SIZE, (float)position_.y * BLOCK_SIZE });
    window.draw(shape_);
}