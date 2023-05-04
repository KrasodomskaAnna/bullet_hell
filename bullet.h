#ifndef BULLET_HELL_3_BULLET_H
#define BULLET_HELL_3_BULLET_H
#pragma once
#include "const.h"
#include "player.h"
#include "collision.h"

enum class BulletType {
    enemy,
    player,
    // greater, firework i shard nigdy nie moze byc wypuszczony przez playera
    greater,
    firework,
    shard
};

class Bullet : public Entity {
public:
    Bullet(math_vector position, SDL_Texture *texture, float speed, float angle, BulletType type);
    BulletType type;
    // zmienia pozycje pocisku symulujac to jak by sie zachowal "w swiecie" -> symuluje tarcie w grze
    // zwraca true gdy pocisk wyhamuje, w przeciwnym wypadku zwraca false
    bool update();
    float getAngle() {
        return this->angle;
    }
    // funkcja sprawdza czy pocisk koliduje z ktorymkolwiek obiektem w wektorze
    // zwraca true gdy koliduje z jakimkolwiek, w przeciwny wypadku zwraca false
    template <class T>
    bool willCollide(Vector<T> &objects);
private:
    float speed;
    float angle;
};

template <class T>
bool Bullet::willCollide(Vector<T> &objects) {
    for(int i = 0; i < objects.size(); i++){
        if(willCollideBox(this->getPos().x, this->getPos().y, this->currentFrame.w, this->currentFrame.h, objects[i]->getPos().x, objects[i]->getPos().y, objects[i]->currentFrame.w, objects[i]->currentFrame.h))
            return true;
    }
    return false;
}


#endif //BULLET_HELL_3_BULLET_H
