#pragma once

#include <string>
#include <SFML/Graphics.hpp>



class Window
{
public:
    Window(const std::string& title, const sf::Vector2u& size);
    virtual ~Window();

    void Update();
    void BeginDraw();
    void Draw(sf::Drawable& drawable_object);
    void EndDraw();

    bool CheckIsDone();
    sf::Vector2u GetWindowSize();


private:
    void Create();
    void Destroy();

    sf::RenderWindow window_;
    bool is_done_ = false;
    std::string default_title_;
    sf::Vector2u default_size_;
};

