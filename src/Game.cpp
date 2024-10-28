
#include "Game.hpp"
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <iostream>
#include <iterator>

Game::Game() { }

Game::~Game() { }

void Game::init(const char *title, int xpos, int ypos, int width, int height,
    bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL_Init failed";
        goto failed;
    }
    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow failed";
        goto failed;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer failed";
        goto failed;
    }
    isRunning = true;
    std::cout << "Hello!\n";
    return;
failed:
    isRunning = false;
}
void Game::handleEvents()
{

    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
        isRunning = false;
}
void Game::update()
{
    cnt++;
    std::cout << cnt << '\n';
}
void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Bye!\n";
}
