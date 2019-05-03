#pragma once
#include <SFML/Graphics.hpp>


class Apple
{
public:
    Apple() = default;
    virtual ~Apple() = default;

    void Create(sf::Vector2i& new_position);

    sf::Vector2i GetPosition() const;

    void Update(const float dt);//пустое тело , т.к по сути яблоко просто лежит пока его не съели
    void Render(sf::RenderWindow& window);//рисует кружочек в нужном месте

private:
    sf::Vector2i position_;
    sf::CircleShape shape_;
};