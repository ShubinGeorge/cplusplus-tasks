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
    void HandleInput();

private:
    Window main_window_;

    sf::Texture grow_tree_image_;
    sf::Texture adult_tree_image_;
    sf::Texture burn_tree_image_;

    Forest forest_;

    sf::CircleShape grow_tree_;
    sf::CircleShape adult_tree_;
    sf::CircleShape burn_tree_;

    const int image_radius_ = 30;
};


