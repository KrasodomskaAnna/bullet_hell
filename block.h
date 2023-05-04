#ifndef BULLET_HELL_2_BLOCK_H
#define BULLET_HELL_2_BLOCK_H
#pragma once
#include "entity.h"

class Block : public Entity {
public:
    Block(float posX, float posY, SDL_Texture *texture) : Entity(texture)
    {
        setPos(posX, posY);
        this->texture = texture;
    }
    uint32_t destroyedAt = 0;
};


#endif //BULLET_HELL_2_BLOCK_H
