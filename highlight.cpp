#include "highlight.h"
#include "random.h"

Highlight::Highlight(SDL_Texture *texture, Shape shape, int boardW, int boardH) : Entity(texture) {
    this->setPos(randomMax(boardW - this->currentFrame.w/2), randomMax(boardH - this->currentFrame.h/2));
    this->shape = shape;
    this->creationTime = SDL_GetTicks();
}

Highlight::Highlight(SDL_Texture *texture, Shape shape) : Entity(texture) {
    this->shape = shape;
    this->creationTime = SDL_GetTicks();
}