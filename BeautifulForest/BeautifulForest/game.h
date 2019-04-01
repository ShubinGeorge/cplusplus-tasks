#pragma once
#include <iostream>
#include <vector>
#include "forest.h"
#include "window.h"

class Game
{
public:
    Game();
    virtual ~Game() = default;

    void Run();
    void Update();
    void Render();

private:
    Window main_window_;

    sf::Texture grow_tree_image_;
    sf::Texture adult_tree_image_;
    sf::Texture burn_tree_image_;

    std::vector<std::vector<sf::CircleShape>> pictures_;
    Forest forest_;

    const int image_radius_ = 30;
};


