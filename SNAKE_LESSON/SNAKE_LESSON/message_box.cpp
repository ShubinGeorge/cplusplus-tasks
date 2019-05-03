#include "message_box.h"


extern const sf::Vector2i WORLD_SIZES;
extern const int BLOCK_SIZE;
extern const sf::Vector2u WINDOW_SIZES;

MessageBox::MessageBox(const sf::Vector2i& position, const sf::Vector2i& sizes,
    const int char_size)
{
    font_.loadFromFile("../Data/fonts/FreeSerif.ttf");
    all_messages_.setFont(font_);

    Create(position, sizes, char_size);
}


void MessageBox::Create(const sf::Vector2i& position, const sf::Vector2i& sizes,
    const int char_size)
{
    background_.setPosition({0, (float)WORLD_SIZES.y * BLOCK_SIZE});
    background_.setSize({(float)sizes.x, (float)sizes.y});
    //background_.setSize({(float)WINDOW_SIZES.x, (float)(WINDOW_SIZES.y - WORLD_SIZES.y * BLOCK_SIZE)});//????
    background_.setFillColor(sf::Color::Black);

    all_messages_.setPosition(
        static_cast<float>(position.x),
        static_cast<float>(position.y)
    );
    all_messages_.setCharacterSize(char_size);
    all_messages_.setFillColor(sf::Color::White);
    
}


void MessageBox::Add(const std::string& new_message)
{
    messages_.push_back(new_message);
}


void MessageBox::Render(sf::RenderWindow& window)
{
    window.draw(background_);

    std::string all_visible_messages;
    for (const std::string& message : messages_)
    {
        all_visible_messages += (message + "\n");
    }

    all_messages_.setString(all_visible_messages);
    window.draw(all_messages_);
}


void MessageBox::Update(const float dt)
{
    //проверять , сколько сообщений помещается в message_box
    const float vertical_size = background_.getSize().y; // in pixels 
    const float line_height = font_.getLineSpacing( // in pixels 
        all_messages_.getCharacterSize()
    );
    const size_t visible_messages_count = static_cast<size_t>(
        vertical_size / line_height);

    while (messages_.size() > visible_messages_count)
    {
        messages_.erase(messages_.begin());
    }
}

