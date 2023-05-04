#include "enemy_move.h"

void executingMoveUpEnemy(Game* game, int index) {
    math_vector newPosition = {game->enemies[index]->getPos().x, game->enemies[index]->getPos().y - (float)STEP};
    // zakoncz, jezeli gracz w nowej pozycji kolidowalby z ktorymkolwiek z blokow, przeciwnikow, z graczem
    if(game->enemies[index]->willCollide(newPosition, game->blocks))
        return;
    if(game->enemies[index]->willCollide(newPosition, game->enemies, index))
        return;
    if(game->enemies[index]->willCollide(newPosition, game->player))
        return;
    // jezeli nie bedzie z nikim kolidował, przesun
    game->enemies[index]->moveUp();
}

void executingMoveDownEnemy(Game* game, int index) {
    math_vector newPosition = {game->enemies[index]->getPos().x, game->enemies[index]->getPos().y + (float) STEP};
    // zakoncz, jezeli gracz w nowej pozycji kolidowalby z ktorymkolwiek z blokow, przeciwnikow, z graczem
    if(game->enemies[index]->willCollide(newPosition, game->blocks))
        return;
    if(game->enemies[index]->willCollide(newPosition, game->enemies, index))
        return;
    if(game->enemies[index]->willCollide(newPosition, game->player))
        return;
    // jezeli nie bedzie z nikim kolidował, przesun
    game->enemies[index]->moveDown();
}

void executingMoveLeftEnemy(Game* game, int index) {
    math_vector newPosition = {game->enemies[index]->getPos().x - (float)STEP, game->enemies[index]->getPos().y};
    // zakoncz, jezeli gracz w nowej pozycji kolidowalby z ktorymkolwiek z blokow, przeciwnikow, z graczem
    if(game->enemies[index]->willCollide(newPosition, game->blocks))
        return;
    if(game->enemies[index]->willCollide(newPosition, game->enemies, index))
        return;
    if(game->enemies[index]->willCollide(newPosition, game->player))
        return;
    // jezeli nie bedzie z nikim kolidował, przesun
    game->enemies[index]->moveLeft();
}

void executingMoveRightEnemy(Game* game, int index){
    math_vector newPosition = {game->enemies[index]->getPos().x + (float)STEP, game->enemies[index]->getPos().y};
    // zakoncz, jezeli gracz w nowej pozycji kolidowalby z ktorymkolwiek z blokow, przeciwnikow, z graczem
    if(game->enemies[index]->willCollide(newPosition, game->blocks))
        return;
    if(game->enemies[index]->willCollide(newPosition, game->enemies, index))
        return;
    if(game->enemies[index]->willCollide(newPosition, game->player))
        return;
    // jezeli nie bedzie z nikim kolidował, przesun
    game->enemies[index]->moveRight();
}