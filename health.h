#ifndef BULLET_HELL_5_HEALTH_H
#define BULLET_HELL_5_HEALTH_H
#pragma once
#include "individual.h"
#include "random.h"
#include "game_window.h"

class Health : public Individual {
public:
    Health(GameWindow* gameWindow, SDL_Texture* bonusHealthTexture) : Individual(gameWindow, bonusHealthTexture, nullptr) {
        this->gameWindow = gameWindow;
        this->texture = bonusHealthTexture;
        this->setPos(0,0);
    }
    bool isDisplay = false;
    void display() {
        startTime = SDL_GetTicks();
        isDisplay = true;
    }
    void hide() {
        isDisplay = false;
    }
    SDL_Texture* texture;
    uint32_t getStartTime() {
        return startTime;
    }
private:
    GameWindow* gameWindow;
    uint32_t startTime;
};


#endif //BULLET_HELL_5_HEALTH_H
