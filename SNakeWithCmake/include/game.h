#pragma once

#include "window.h"
#include "message_box.h"
#include "world.h"
#include "message_box.h"

class Game
{
public:
    Game();
    virtual ~Game() = default;

    void Run();
    void HandleInput();
    void Update(const float dt);
    void Render();
    void AddMessage();

private:
    Window main_window_;
    World world_;
    MessageBox message_box_;
};

