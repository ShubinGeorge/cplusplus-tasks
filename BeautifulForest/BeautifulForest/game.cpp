#include <iostream>
#include "game.h"
#include "forest.h"


Game::Game()
    : main_window_("Leto 2010", sf::Vector2u(600, 600)), forest_(10, 10)
{
    forest_.SetValue(5, 5, 10, 0, 1); // задаем позицию, броню,здоровье для горящего дерева в лесу  

    pictures_.reserve(forest_.GetHeight());
    for (size_t i = 0; i < forest_.GetHeight(); i++)
    {
        std::vector<sf::CircleShape> line;
        line.reserve(forest_.GetWidth());
        for (size_t j = 0; j < forest_.GetWidth(); j++)
        {
            sf::CircleShape tree;
            tree.setRadius(image_radius_);
            tree.setFillColor(sf::Color::White);
            line.push_back(tree);
        }
        pictures_.push_back(line);
    }

    grow_tree_image_.loadFromFile("../Data/grow_tree2.jpg");
    grow_tree_image_.setSmooth(true);
	
    burn_tree_image_.loadFromFile("../Data/burn_tree2.jpg");
    burn_tree_image_.setSmooth(true);

    adult_tree_image_.loadFromFile("../Data/adult_tree2.jpg");
    adult_tree_image_.setSmooth(true);
}


void Game::Run()
{
    while (!main_window_.CheckIsDone())
    {
        Update();
        Render();
        getchar();
        forest_.Update();
    }
}


void Game::Update()
{
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
                pictures_[i][j].setPosition(sf::Vector2f(image_x_coord, image_y_coord));
                pictures_[i][j].setTexture(&adult_tree_image_);
                main_window_.Draw(pictures_[i][j]);
            }
            if (forest_.GetData()[i][j].current_state_ == STATUS_BURN)
            {
                pictures_[i][j].setPosition(sf::Vector2f(image_x_coord, image_y_coord));
                pictures_[i][j].setTexture(&burn_tree_image_);
                main_window_.Draw(pictures_[i][j]);
            }
            if (forest_.GetData()[i][j].current_state_ == STATUS_DEAD)
            {
                pictures_[i][j].setPosition(sf::Vector2f(image_x_coord, image_y_coord));
                pictures_[i][j].setTexture(&grow_tree_image_);
                main_window_.Draw(pictures_[i][j]);
            }
            image_x_coord += 2 * image_radius_;
        }
        image_x_coord = 0;
        image_y_coord += 2 * image_radius_;
    }
    main_window_.EndDraw();
}