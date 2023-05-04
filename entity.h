#ifndef BULLET_HELL_2_ENTITY_H
#define BULLET_HELL_2_ENTITY_H
#pragma once
#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "math_vector.h"

// klasa Entity przyjmowana przez kazdy element, ktory bedzie wyswietlany na planszy
class Entity {
public:
    Entity(SDL_Texture *texture) {
        if(texture != nullptr){
            currentFrame.x = 0;
            currentFrame.y = 0;
            SDL_QueryTexture(texture, NULL, NULL, &currentFrame.w, &currentFrame.h);
        }
    }
    SDL_Texture *texture;
    math_vector getPos(){
        return position;
    }
    void setPos(float x, float y){
        position = math_vector{x, y};
    }
    SDL_Rect currentFrame;
    math_vector getMiddlePos(){
        return math_vector{this->position.x + this->currentFrame.w/2, this->position.y + this->currentFrame.h/2};
    }
private:
    math_vector position{0.0,0.0};
};


#endif //BULLET_HELL_2_ENTITY_H
