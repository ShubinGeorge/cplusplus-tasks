#pragma once
#include <SFML/Graphics.hpp>


class Wall
{
public:
    Wall() = default;
    virtual ~Wall() = default;

    void Create(const sf::Vector2i& top_left, const sf::Vector2i& bottom_right);

    bool CheckCellInWall(const sf::Vector2i& cell) const;
    //void SetPosition(const sf::Vector2i& position);
    void Update(const float dt);
    void Render(sf::RenderWindow& window);
 
private:
    sf::Vector2i top_left_;//координата верзнего левого угла
    sf::Vector2i bottom_right_;
    
    sf::RectangleShape shape_;
};