#include "individual.h"
#include "game.h"

Individual::Individual(GameWindow *gameWindow, SDL_Texture *texture, SDL_Texture *animationTexture) : Entity(texture)
{
    this->gameWindow = gameWindow;
    this->texture = texture;
    this->animationTexture = animationTexture;
    this->baseTexture = texture;
}

void Individual::changeTexture() {
    this->texture = this->isBaseTexture ? this->animationTexture : this->baseTexture;
    this->isBaseTexture = !this->isBaseTexture;
}
