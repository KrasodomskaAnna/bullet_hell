#ifndef BULLET_HELL_5_HIGHLIGHT_H
#define BULLET_HELL_5_HIGHLIGHT_H
#pragma once
#include "entity.h"

enum class Shape {
    square,
    rectangleH,
    rectangleV
};

class Highlight : public Entity {
public:
    Highlight(SDL_Texture *texture, Shape shape, int boardW, int boardH);
    Highlight(SDL_Texture *texture, Shape shape);
    Shape shape;
    uint32_t getCreationTime() {
        return creationTime;
    }
private:
    uint32_t creationTime;
};


#endif //BULLET_HELL_5_HIGHLIGHT_H
