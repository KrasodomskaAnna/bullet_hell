#ifndef BULLET_HELL_5_PLAYER_MOVE_H
#define BULLET_HELL_5_PLAYER_MOVE_H
#pragma once
#include "const.h"
#include "game.h"

// funkcje obsluguja ruch gracza w odpowiednia strone
void executingMoveUp(Game* game);
void executingMoveDown(Game* game);
void executingMoveLeft(Game* game);
void executingMoveRight(Game* game);

// funkcje symuluja nieprzesuwanie sie elementow w trakcie ruchu gracza w odpowiednia strone
void simulatingNotMoveElementsUp(Game* game);
void simulatingNotMoveElementsDown(Game* game);
void simulatingNotMoveElementsLeft(Game* game);
void simulatingNotMoveElementsRight(Game* game);

enum class Directions {
    up,
    down,
    right,
    left
};

template <class T>
void simulatingNotMoveListUp(List <T*> object, Directions direction) {
    // jezeli istnieje jakis element listy
    if (object.head == nullptr)
        return;

    float deltaX = 0;
    float deltaY = 0;
    switch(direction) {
        case Directions::up:
            deltaY += 10;
            break;
        case Directions::down:
            deltaY -= 10;
            break;
        case Directions::right:
            deltaX -= 10;
            break;
        case Directions::left:
            deltaX += 10;
            break;
        default:
            break;
    }

    node<T*> *current = object.getNext(nullptr);
    while (current != nullptr) {
        current->value->setPos(current->value->getPos().x + deltaX, current->value->getPos().y + deltaY);
        current = current->next;
    }
}


#endif //BULLET_HELL_5_PLAYER_MOVE_H
