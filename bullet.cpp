#include "bullet.h"

Bullet::Bullet(math_vector position, SDL_Texture *texture, float speed, float angle, BulletType type) : Entity(texture) {
    this->setPos(position.x, position.y);
    this->speed = speed;
    this->angle = angle;
    this->texture = texture;
    this->type = type;
}

bool Bullet::update() {
    float c = this->speed;
    float a = cos((this->getAngle() * (PI / (FULL_CIRCLE/2)))) * c;
    float b = tan(this->getAngle() * (PI / (FULL_CIRCLE/2))) * a;
    this->setPos(this->getPos().x + a, this->getPos().y + b);
    if(this->type == BulletType::greater)
        this->speed -= GREATER_DRAG;
    if(this->type == BulletType::firework)
        this->speed -= FIREWORK_DRAG;
    if(this->type == BulletType::shard)
        this->speed -= SHARD_DRAG;
    else
        this->speed -= DRAG;
    if (speed < 0) {
        return true;
    }
    return false;
}


