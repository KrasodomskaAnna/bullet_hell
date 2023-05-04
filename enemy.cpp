#include "enemy.h"

void Enemy::shoot(float speed, float angle) {
    switch(type) {
        case EnemyType::even:
            evenShootingPattern(speed, angle, randomMin(FULL_CIRCLE/MIN_CORRIDOR_SPACE));
            break;
        case EnemyType::accent:
            accentShootingPattern(speed, angle, random(MIN_PARTS_OF_CIRCLE_DIVIDE, MAX_PARTS_OF_CIRCLE_DIVIDE), random(MIN_NORMAL_SPACE, MAX_NORMAL_SPACE), random(MIN_CORRIDOR_SPACE,MAX_CORRIDOR_SPACE));
            break;
        case EnemyType::killer:
            killerShootingPattern(angle);
            break;
        case EnemyType::rand:
            randShootingPattern(speed, angle);
            break;
        case EnemyType::custom:
            customShootingPattern();
            break;
        default:
            anyShoot(speed, angle);
            break;
    }
}

void Enemy::anyShoot(float speed, float angle) {
    int i = (int)random(0, 4);
    switch(i % 4) {
        case 0:
            evenShootingPattern(speed, angle, randomMin(FULL_CIRCLE/MIN_CORRIDOR_SPACE));
            break;
        case 1:
            accentShootingPattern(speed, angle, random(MIN_PARTS_OF_CIRCLE_DIVIDE, MAX_PARTS_OF_CIRCLE_DIVIDE), random(MIN_NORMAL_SPACE, MAX_NORMAL_SPACE), random(MIN_CORRIDOR_SPACE,MAX_CORRIDOR_SPACE));
            break;
        case 2:
            killerShootingPattern(angle);
            break;
        default:
            randShootingPattern(speed, angle);
            break;
    }
}

void Enemy::evenShootingPattern(float speed, float angle, int howMuch) {
    for(int i = 0; i < howMuch; i++) {
        this->bullets->addAfter(new Bullet({this->getPos().x + ((float)this->currentFrame.w/2), this->getPos().y + ((float)this->currentFrame.h/2)}, this->bulletsTexture, speed, angle, BulletType::enemy));
        angle += FULL_CIRCLE/howMuch;
    }
}

void Enemy::accentShootingPattern(float speed, float angle, int howMuch, float space, float accent) {
    float circlePart = FULL_CIRCLE/howMuch;
    int howMuchNotAccented = floor((circlePart - 2*accent)/space);
    for(int i = 0; i < howMuch; i++) {
        float bulletAngle = angle + i*circlePart;
        for(int j = 0; j < howMuchNotAccented; j++) {
            this->bullets->addAfter(new Bullet({this->getPos().x + ((float)this->currentFrame.w/2), this->getPos().y + ((float)this->currentFrame.h/2)}, this->bulletsTexture, speed, bulletAngle, BulletType::enemy));
            bulletAngle += space;
        }
        bulletAngle += ((i+1)*circlePart - bulletAngle)/2;
        this->bullets->addAfter(new Bullet({this->getPos().x + ((float)this->currentFrame.w/2), this->getPos().y + ((float)this->currentFrame.h/2)}, this->bulletsTexture, speed, bulletAngle, BulletType::enemy));
    }
}

void Enemy::randShootingPattern(float speed, float angle) {
    float bulletAngle = angle;
    bulletAngle += random(MIN_CORRIDOR_SPACE,MAX_CORRIDOR_SPACE);
    while(bulletAngle < FULL_CIRCLE + angle - random(MIN_CORRIDOR_SPACE,MAX_CORRIDOR_SPACE)) {
        this->bullets->addAfter(new Bullet({this->getPos().x + ((float)this->currentFrame.w/2), this->getPos().y + ((float)this->currentFrame.h/2)}, this->bulletsTexture, speed, bulletAngle, BulletType::enemy));
        bulletAngle += randomMax(MAX_RAND_SPACE);
    }
}

void Enemy::killerShootingPattern(float angle) {
    float bulletAngle = angle - SHOOTS_KILLER_PATTERN*DELTA_KILLER_PATTERN;
    float newSpeed = random(MIN_SPEED, MAX_SPEED);
    for(int i = 0; i<(SHOOTS_KILLER_PATTERN*2 + 1); i++) {
        bulletAngle += DELTA_KILLER_PATTERN;
        this->bullets->addAfter(new Bullet({this->getPos().x + ((float)this->currentFrame.w/2), this->getPos().y + ((float)this->currentFrame.h/2)}, this->bulletsTexture, newSpeed, bulletAngle, BulletType::enemy));
    }
}

void Enemy::customShootingPattern() {
    for (int i = 0; i < this->customShootingPatternItems->size(); i++) {
        this->bullets->addAfter(new Bullet({this->getPos().x + ((float)this->currentFrame.w/2), this->getPos().y + ((float)this->currentFrame.h/2)}, this->bulletsTexture, (*this->customShootingPatternItems)[i].speed, (*this->customShootingPatternItems)[i].angle, BulletType::enemy));
    }
}




void Enemy::moveUp() {
    this->changeTexture();
    if(this->getPos().y - STEP >= CORD_ORIGIN)
        this->setPos(this->getPos().x, this->getPos().y - STEP);
}

void Enemy::moveDown() {
    this->changeTexture();
    if(this->getPos().y + STEP <= gameWindow->getBoardH() - this->currentFrame.h)
        this->setPos(this->getPos().x, this->getPos().y + STEP);
}

void Enemy::moveRight() {
    this->changeTexture();
    if (this->getPos().x + STEP <= gameWindow->getBoardW() - this->currentFrame.w)
        this->setPos(this->getPos().x + STEP, this->getPos().y);
}

void Enemy::moveLeft() {
    this->changeTexture();
    if(this->getPos().x - STEP >= CORD_ORIGIN)
        this->setPos(this->getPos().x - STEP, this->getPos().y);
}
