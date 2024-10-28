#pragma once

#include <SDL2/SDL.h>
class Game {
public:
    Game();
    Game(Game &&) = default;
    Game(const Game &) = default;
    Game &operator=(Game &&) = default;
    Game &operator=(const Game &) = default;
    ~Game();

    void init(const char *title, int xpos, int ypos, int width, int height,
        bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() { return isRunning; };

private:
    int cnt = 0;

    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
};
