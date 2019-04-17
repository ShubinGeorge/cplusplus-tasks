#include "window.h"
#include "partical_system.h"


Window::Window(const std::string& title, const sf::Vector2u& size)
{
    is_done_ = false;
    default_title_ = title;
    default_size_ = size;

    Create();
}


Window::~Window()
{
    Destroy();
}


void Window::Update(const float dt)
{
    sf::Event event;
    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            is_done_ = true;
        }

        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::Escape:
                    is_done_ = true;
                    break;

                default:;
            }
        }
    }
}


void Window::BeginDraw()
{
    window_.clear(sf::Color(224, 224, 148));
}


void Window::Draw(sf::Drawable& drawable_object)
{
    window_.draw(drawable_object);
}


void Window::Draw(Particle& particle)
{
    particle.Render(window_);
}


void Window::EndDraw()
{
    window_.display();
}


bool Window::CheckIsDone()
{
    return is_done_;
}


sf::Vector2u Window::GetWindowSize()
{
    return window_.getSize();
}


void Window::Create()
{
    window_.create(
        sf::VideoMode(default_size_.x, default_size_.y),
        default_title_,
        sf::Style::Titlebar | sf::Style::Close
    );
}


void Window::Destroy()
{
    window_.close();
}


sf::RenderWindow& Window::GetWindow()
{
    return window_;
}