#ifndef BULLET_HELL_5_ENEMY_MOVE_H
#define BULLET_HELL_5_ENEMY_MOVE_H
#pragma once
#include "game.h"

// funkcje obsluguja ruch przeciwnika w odpowiednia strone
void executingMoveUpEnemy(Game* game, int index);
void executingMoveDownEnemy(Game* game, int index);
void executingMoveRightEnemy(Game* game, int index);
void executingMoveLeftEnemy(Game* game, int index);

#endif //BULLET_HELL_5_ENEMY_MOVE_H
