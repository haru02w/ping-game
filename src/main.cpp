#include "Game.hpp"
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[])
{
    std::srand(-1);
    auto op_game = Game::create(argv[0]);
    if (op_game.has_value())
        op_game.value()->run();
    else
        std::cerr << "Couldn't create game";

    return 0;
}
