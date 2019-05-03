#include <iostream>
#include "game.h"
#include <SFML/Graphics.hpp>
//#include "message_box.h"
int main()
{

    //MessageBox message_box({ 10, 10 }, { 50, 10 }, 5);
    Game game;
    game.Run();
   
    return 0;
}