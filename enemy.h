#ifndef BULLET_HELL_3_ENEMY_H
#define BULLET_HELL_3_ENEMY_H
#pragma once
#include "individual.h"
#include "bullet.h"
#include "list.h"
#include "random.h"


enum class EnemyType {
    even,
    accent,
    killer,
    rand,
    any,
    custom
};

struct BulletConfig {
    float speed = 0.0;
    int angle = 0;
};

class Enemy : public Individual {
public:
    Enemy(GameWindow *gameWindow, float posX, float posY, SDL_Texture *texture, SDL_Texture *animationTexture, List<Bullet*>* bullets, SDL_Texture *bulletsTexture, EnemyType type) : Individual(gameWindow, texture, animationTexture) {
        setPos(posX, posY);
        this->bullets = bullets;
        this->bulletsTexture = bulletsTexture;
        this->type = type;
    }
    Enemy(GameWindow *gameWindow, float posX, float posY, SDL_Texture *texture, SDL_Texture *animationTexture, List<Bullet*>* bullets, SDL_Texture *bulletsTexture, EnemyType type, Vector<BulletConfig> *customShootingPattern) : Individual(gameWindow, texture, animationTexture) {
        setPos(posX, posY);
        this->bullets = bullets;
        this->bulletsTexture = bulletsTexture;
        this->type = type;
        this->customShootingPatternItems = customShootingPattern;
    }

    int getHealth() {
        return health;
    }
    void setHealth(int newHealth) {
        this->health = newHealth;
    }
    // funkcja obsluguje strzelanie przeciwnika, jako argumenty przyjmuje predkość i kat z jakim ma byc wystrzelony pocisk
    void shoot(float speed, float angle);
    void anyShoot(float speed, float angle);
    // patterny strzelnia po okregu: rownomierne, akcentujace wskazana ilosc pociskow, z randomowa przerwa, pattern wystrzeliwywania kilku szybszych pociskow prosto w gracza
    void evenShootingPattern(float speed, float angle, int howMuch);
    void accentShootingPattern(float speed, float angle, int howMuch, float space, float accent);
    void randShootingPattern(float speed, float angle);
    void killerShootingPattern(float angle);
    void customShootingPattern();
    EnemyType getType() {
        return type;
    }
    // funkcje obsluguja przemieszczanie się jezeli zmiana pozycji nie powoduje, iz obiekt znajdzie sie poza plansza
    // w przeciwnym razie ustawia krawedz styku
    virtual void moveUp() override;
    virtual void moveDown() override;
    virtual void moveRight() override;
    virtual void moveLeft() override;
    ~Enemy() {
        delete this->customShootingPatternItems;
    }
private:
    List<Bullet*>* bullets;
    SDL_Texture *bulletsTexture;
    EnemyType type;
    int health = 100;
    Vector<BulletConfig>* customShootingPatternItems = nullptr;
};


#endif //BULLET_HELL_3_ENEMY_H
