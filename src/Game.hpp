#pragma once
#include "Entities.hpp"
#include <SDL.h>
#include <SDL_rect.h>
#include <memory>
#include <optional>
#include <vector>

class Game {
public:
    static std::optional<std::unique_ptr<Game>> create(const char *title);

    void run();

    Game(Game &&) = default;
    Game &operator=(Game &&) = default;
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;
    ~Game();

    enum {
        BALL_0,
        PADDLE_0,
    };

private:
    Game() = default;
    void handleInput();
    void update();
    void render();

    // Entities
    std::vector<std::unique_ptr<Entity>> mEntities;
    // Global
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;

    // end
    bool mFinish = false;
};
