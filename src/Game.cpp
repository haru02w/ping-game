#include "Game.hpp"
#include <SDL.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <optional>
#include <ostream>

using std::make_optional;

std::optional<std::unique_ptr<Game>> Game::create(const char *title)
{
    std::unique_ptr<Game> game(new Game);
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return std::nullopt;

    SDL_DisplayMode dm;

    if (SDL_GetCurrentDisplayMode(0, &dm) != 0)
        return std::nullopt;

    game->mWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, dm.w / 2, dm.h / 2, SDL_WINDOW_SHOWN);

    if (game->mWindow == nullptr)
        return std::nullopt;

    game->mRenderer
        = SDL_CreateRenderer(game->mWindow, -1, SDL_RENDERER_ACCELERATED);

    if (game->mRenderer == nullptr)
        return std::nullopt;

    game->mEntities.emplace(std::begin(game->mEntities) + Game::BALL_0,
        std::make_unique<Ball>(game->mRenderer));
    game->mEntities.emplace(std::begin(game->mEntities) + Game::PADDLE_0,
        std::make_unique<Paddle>(game->mRenderer));

    return make_optional(std::move(game));
}

Game::~Game()
{

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::run()
{
    Uint32 nowFrameTime = 0;
    Uint32 prevFrameTime = 0;

    while (!mFinish) {

        handleInput();

        nowFrameTime = SDL_GetTicks();
        if (nowFrameTime - prevFrameTime > 1000 / 60.0) {
            prevFrameTime = nowFrameTime;

            update();
            render();
        };
    }
}

void Game::handleInput()
{
    static SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            mFinish = true;
        else {
            std::for_each(mEntities.cbegin(), mEntities.cend(),
                [](const std::unique_ptr<Entity> &e) {
                    e->handleInput(event);
                });
        }
    }
}

void Game::update()
{
    std::for_each(mEntities.cbegin(), mEntities.cend(),
        [this](const std::unique_ptr<Entity> &e) { e->update(mEntities); });
}

void Game::render()
{

    if (SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255))
        std::cout << SDL_GetError();
    if (SDL_RenderClear(mRenderer))
        std::cout << SDL_GetError();

    std::for_each(mEntities.cbegin(), mEntities.cend(),
        [this](const std::unique_ptr<Entity> &e) { e->render(mRenderer); });

    SDL_RenderPresent(mRenderer);
}
