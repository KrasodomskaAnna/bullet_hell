#ifndef BULLET_HELL_2_INDIVIDUAL_H
#define BULLET_HELL_2_INDIVIDUAL_H
#pragma once
#include "game_window.h"
#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "math_vector.h"
#include "entity.h"
#include "vector.h"
#include "block.h"
#include "const.h"
#include "collision.h"

enum class Hitboxes
{
    none,
    all,
    head,
    torso,
    legs
};

// klasa Entity przyjmowana przez kazdy obiekt, ktory bedzie "funkcjonowal samodzielnie" -> obsługuje poruszanie
class Individual : public Entity
{
public:
    Individual(GameWindow *gameWindow, SDL_Texture *baseTexture, SDL_Texture *animationTexture);

    // funkcja sprawdza czy obiekt koliduje z ktorymkolwiek obiektem w wektorze
    // zwraca true gdy koliduje z jakimkolwiek, w przeciwny wypadku zwraca false
    template <class T>
    bool willCollide(math_vector newPosition, Vector<T> &objects);
    // .._.. pomija jeden element wektoru
    template <class T>
    bool willCollide(math_vector newPosition, Vector<T> &objects, int skipIndex);
    // .._.. sprawdza dla obiektu
    template <class T>
    bool willCollide(math_vector newPosition, T &object);
    // sprawdza w ktora czesc ciala zostal uderzonyobiekt, zwraca enum
    template <class T>
    Hitboxes willCollideHitboxes(math_vector newPosition, T &object);

    // funkcje osluguja przemieszczanie się
    virtual void moveUp(){};
    virtual void moveDown(){};
    virtual void moveRight(){};
    virtual void moveLeft(){};

protected:
    GameWindow *gameWindow;
    void changeTexture();
    bool isBaseTexture = true;
    SDL_Texture *animationTexture;
    SDL_Texture *baseTexture;
};

template <class T>
bool Individual::willCollide(math_vector newPosition, Vector<T> &objects)
{
    for (int i = 0; i < objects.size(); i++){
        if(willCollideBox(newPosition.x, newPosition.y, this->currentFrame.w, this->currentFrame.h, objects[i]->getPos().x, objects[i]->getPos().y, objects[i]->currentFrame.w, objects[i]->currentFrame.h))
            return true;
    }
    return false;
}

template <class T>
bool Individual::willCollide(math_vector newPosition, Vector<T> &objects, int skipIndex)
{
    for (int i = 0; i < objects.size(); i++)
    {
        if (i == skipIndex)
            continue;
        if(willCollideBox(newPosition.x, newPosition.y, this->currentFrame.w, this->currentFrame.h, objects[i]->getPos().x, objects[i]->getPos().y, objects[i]->currentFrame.w, objects[i]->currentFrame.h))
            return true;
    }
    return false;
}

template <class T>
bool Individual::willCollide(math_vector newPosition, T &object)
{
    return willCollideBox(newPosition.x, newPosition.y, this->currentFrame.w, this->currentFrame.h, object->getPos().x, object->getPos().y, object->currentFrame.w, object->currentFrame.h);
}

template <class T>
Hitboxes Individual::willCollideHitboxes(math_vector newPosition, T &object)
{
    if (willCollideBox(newPosition.x, newPosition.y, this->currentFrame.w, this->currentFrame.h / 3, object->getPos().x, object->getPos().y, object->currentFrame.w, object->currentFrame.h))
        return Hitboxes::head;

    if (willCollideBox(newPosition.x, newPosition.y + this->currentFrame.h / 3, this->currentFrame.w, this->currentFrame.h / 3, object->getPos().x, object->getPos().y, object->currentFrame.w, object->currentFrame.h))
        return Hitboxes::torso;

    if (willCollideBox(newPosition.x, newPosition.y + this->currentFrame.h * 2 / 3, this->currentFrame.w, this->currentFrame.h / 3, object->getPos().x, object->getPos().y, object->currentFrame.w, object->currentFrame.h))
        return Hitboxes::legs;

    return Hitboxes::none;
}

#endif //BULLET_HELL_2_INDIVIDUAL_H
