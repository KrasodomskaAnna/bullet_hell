#ifndef BULLET_HELL_2_PLAYER_H
#define BULLET_HELL_2_PLAYER_H
#pragma once
#include "const.h"
#include "game_window.h"
#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "math_vector.h"
#include "individual.h"

// zapis krawedzi styku
enum Edges {
    None = 0,
    Left = 1,
    Right = 2,
    Up = 3,
    Down = 4
};

class Player : public Individual {
public:
    Player(GameWindow* gameWindow, const char* texturePath, const char* animationTexturePath);

    uint32_t hitTime;
    int getHealth() {
        return health;
    }
    void setHealth(int newHealth) {
        this->health = newHealth;
    }
    Edges getTouchedEdge(){
        return edge;
    }
    void setEdge(Edges newEdge){
        edge = newEdge;
    }

    // funkcje osluguja przemieszczanie się
    // jezeli zmiana pozycji nie powoduje, iz obiekt nie będzie w wyswietlanym okienku ustawia pozycje
    // w przeciwnym razie ustawia krawedz styku
    virtual void moveUp() override;
    virtual void moveDown() override;
    virtual void moveRight() override;
    virtual void moveLeft() override;
private:
    int health = 100;
    Edges edge = None;
};


#endif //BULLET_HELL_2_PLAYER_H
