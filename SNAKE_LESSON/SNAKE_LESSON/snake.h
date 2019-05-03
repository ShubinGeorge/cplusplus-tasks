#pragma once
#include <SFML/Graphics.hpp>


class Snake
{
public:
    struct Segment
    {
        sf::Vector2i position;
        sf::RectangleShape shape;
        sf::Color color;
    };

    enum Direction
    {
        Up,
        Right,
        Down,
        Left,
        None
    };

public:
    Snake() = default;
    virtual ~Snake() = default;

    void Create(const sf::Vector2i& head_position);

    Direction GetDirection() const;
    void SetDirection(const Direction new_direction);
    int GetScore() const;
    void IncreaseScore(const int delta_score);
    int GetLives() const;
    void DecreaseLivesByOne();

    bool CheckSelfCollision() const;

    sf::Vector2i GetHeadPosition() const;
    const std::vector<Segment>& GetBody() const;

    void Update(const float dt);
    void Render(sf::RenderWindow& window);
    void Grow();
    void RespawnSnake();

private:
    void MoveByOneCell();

    std::vector<Segment> body_;
    Direction direction_;
    int lives_ = 2;
    int score_ = 0;
};