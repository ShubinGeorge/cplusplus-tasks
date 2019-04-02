#include <iostream>
#include "game.h"
#include "forest.h"


Game::Game()
    : main_window_("Leto 2010", sf::Vector2u(600, 600)), forest_(10, 10)
{
    forest_.SetValue(5, 5, 10, 0, 1); 

    grow_tree_image_.loadFromFile("../Data/grow_tree2.jpg");
    grow_tree_image_.setSmooth(true);
    grow_tree_.setTexture(&grow_tree_image_);
    grow_tree_.setRadius(image_radius_);
    grow_tree_.setFillColor(sf::Color::White);

    burn_tree_image_.loadFromFile("../Data/burn_tree2.jpg");
    burn_tree_image_.setSmooth(true);
    burn_tree_.setTexture(&burn_tree_image_);
    burn_tree_.setRadius(image_radius_);
    burn_tree_.setFillColor(sf::Color::White);

    adult_tree_image_.loadFromFile("../Data/adult_tree2.jpg");
    adult_tree_image_.setSmooth(true);
    adult_tree_.setTexture(&adult_tree_image_);
    adult_tree_.setRadius(image_radius_);
    adult_tree_.setFillColor(sf::Color::White);

}


void Game::HandleInput()
{
    getchar();
}


void Game::Run()
{
    while (!main_window_.CheckIsDone())
    {
        Update();
        Render();
        HandleInput();
    }
}


void Game::Update()
{
    forest_.Update();
    main_window_.Update();
}


void Game::Render()
{
    int image_x_coord = 0;
    int image_y_coord = 0;

    main_window_.BeginDraw();	
    for (size_t i = 0; i < forest_.GetHeight(); i++)
    {
        for (size_t j = 0; j < forest_.GetWidth(); j++)
        {
            if (forest_.GetData()[i][j].current_state_ == STATUS_GROW)
            {
                adult_tree_.setPosition(sf::Vector2f(image_x_coord, image_y_coord));
                main_window_.Draw(adult_tree_);
            }
            if (forest_.GetData()[i][j].current_state_ == STATUS_BURN)
            {
                burn_tree_.setPosition(sf::Vector2f(image_x_coord, image_y_coord));
                main_window_.Draw(burn_tree_);
            }
            if (forest_.GetData()[i][j].current_state_ == STATUS_DEAD)
            {
                grow_tree_.setPosition(sf::Vector2f(image_x_coord, image_y_coord));
                main_window_.Draw(grow_tree_);
            }
            image_x_coord += 2 * image_radius_;
        }
        image_x_coord = 0;
        image_y_coord += 2 * image_radius_;
    }
    main_window_.EndDraw();
}