#pragma once
#include <SDL.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <cmath>
#include <memory>
#include <vector>

class Entity {
public:
    virtual ~Entity() = default;
    virtual void update(std::vector<std::unique_ptr<Entity>> &entities) = 0;
    virtual void render(SDL_Renderer *renderer) = 0;
    virtual void handleInput(SDL_Event &event) = 0;
    SDL_Rect mRect;
};

class Paddle : public Entity {
public:
    explicit Paddle(SDL_Renderer *renderer);
    virtual void update(
        std::vector<std::unique_ptr<Entity>> &entities) override;
    virtual void render(SDL_Renderer *renderer) override;
    virtual void handleInput(SDL_Event &event) override;

    SDL_Rect mRect;

private:
    enum { VELOCITY_CHANGE = 10 };
    int mVelX;

    int mMaxW;
};

class Ball : public Entity {
public:
    explicit Ball(SDL_Renderer *renderer);
    virtual void update(
        std::vector<std::unique_ptr<Entity>> &entities) override;
    virtual void render(SDL_Renderer *renderer) override;
    virtual void handleInput(SDL_Event &event) override;

    SDL_Rect mRect;

private:
    void startBall();
    enum { VELOCITY_CHANGE = 16 };
    int mVelX, mVelY;
    int mMaxW, mMaxH;
};
