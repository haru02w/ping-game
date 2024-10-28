#include "Game.hpp"
#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char *argv[])
{
    Game game;
    game.init(nullptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
        true);

    while (game.running()) {
        game.handleEvents();
        game.update();
        game.render();
    }
    game.clean();
    return 0;
}
