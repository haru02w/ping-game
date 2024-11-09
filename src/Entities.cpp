#include "Entities.hpp"
#include "Game.hpp"
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_render.h>
#include <cstdlib>
#include <iostream>
#include <ostream>

Paddle::Paddle(SDL_Renderer *renderer)
    : mVelX(0)
{

    int y;
    SDL_GetRendererOutputSize(renderer, &mMaxW, &y);
    mRect.w = mMaxW / 4;
    mRect.h = y / 32;

    mRect.y = y - mRect.h;
    mRect.x = (mMaxW - mRect.w) / 2; // start of the paddle width
}

void Paddle::update(std::vector<std::unique_ptr<Entity>> &entities)
{

    int nextPos = mRect.x + mVelX;
    if (nextPos <= 0)
        mRect.x = 0;
    else if (nextPos + mRect.w >= mMaxW)
        mRect.x = mMaxW - mRect.w;
    else
        mRect.x = nextPos;
}

void Paddle::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &mRect);
}

void Paddle::handleInput(SDL_Event &event)
{
    if (event.key.repeat != 0)
        return;

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_a:
            mVelX -= Paddle::VELOCITY_CHANGE;
            break;
        case SDLK_d:
            mVelX += Paddle::VELOCITY_CHANGE;
            break;
        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
        case SDLK_a:
            mVelX += Paddle::VELOCITY_CHANGE;
            break;
        case SDLK_d:
            mVelX -= Paddle::VELOCITY_CHANGE;
            break;
        }
    }
}

Ball::Ball(SDL_Renderer *renderer)
{
    SDL_GetRendererOutputSize(renderer, &mMaxW, &mMaxH);

    mRect.w = 20;
    mRect.h = 20;

    startBall();
}

void Ball::startBall()
{
    mRect.x = (mMaxW - mRect.w) / 2;
    mRect.y = (mMaxH - mRect.h) / 2;

    int vel = (std::rand() % (VELOCITY_CHANGE - 2)) + 2;
    int velComplement = VELOCITY_CHANGE - vel;
    mVelY = std::rand() % 2 ? vel : -vel;
    mVelX = std::rand() % 2 ? velComplement : -velComplement;
}

void Ball::update(std::vector<std::unique_ptr<Entity>> &entities)
{
    static int i = 0;
    int nextPosX = mRect.x + mVelX;
    int nextPosY = mRect.y + mVelY;

    Paddle &paddle = dynamic_cast<Paddle &>(*entities.at(Game::PADDLE_0));

    if (nextPosY + mRect.h >= paddle.mRect.y
        && nextPosX + mRect.w >= paddle.mRect.x
        && nextPosX <= paddle.mRect.x + paddle.mRect.w) {

        mRect.y = paddle.mRect.y - mRect.h;
        int paddleMiddle = (paddle.mRect.w / 2) + paddle.mRect.x;

        mVelX = ((nextPosX - paddleMiddle) / ((double)paddle.mRect.w / 2.0))
            * (double)Ball::VELOCITY_CHANGE;

        if (mVelX >= 12)
            mVelX = 12;
        else if (mVelX <= -12)
            mVelX = -12;

        mVelY = -(Ball::VELOCITY_CHANGE - std::abs(mVelX));
    }

    if (nextPosX <= 0) {
        mRect.x = 0;
        mVelX = -mVelX;
    } else if (nextPosX + mRect.w >= mMaxW) {
        mRect.x = mMaxW - mRect.w;
        mVelX = -mVelX;
    } else {
        mRect.x += mVelX;
    }

    if (nextPosY <= 0) {
        mRect.y = 0;
        mVelY = -mVelY;
    } else if (nextPosY + mRect.h >= mMaxH) {
        startBall();
    } else {
        mRect.y += mVelY;
    }

no_colision:
}

void Ball::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &mRect);
}

void Ball::handleInput(SDL_Event &event)
{
    /* maybe later, to pause the game */
}
