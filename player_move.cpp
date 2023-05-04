#include "player_move.h"

void executingMoveUp(Game* game)
{
    math_vector newPosition = {game->player->getPos().x, game->player->getPos().y - (float)STEP};
    // zakoncz, jezeli gracz w nowej pozycji kolidowalby z ktorymkolwiek z blokow, przeciwnikow,
    if(game->player->willCollide(newPosition, game->blocks))
        return;
    if(game->player->willCollide(newPosition, game->enemies))
        return;

    // jezeli nie bedzie kolidowal, moze sie przesunac
    game->player->moveUp();

    // jezeli gracz dotknal krawedzi, a nie jest na koncu planszy, nalezy "przesunac ekran"
    if(game->player->getTouchedEdge() == Up)
    {
        if(game->gameWindow->getPos().y + STEP <= 0.0)
            simulatingNotMoveElementsUp(game);
    }
}

void executingMoveDown(Game* game)
{
    math_vector newPosition = {game->player->getPos().x, game->player->getPos().y + (float)STEP};
    // zakoncz, jezeli gracz w nowej pozycji kolidowalby z ktorymkolwiek z blokow, przeciwnikow,
    if(game->player->willCollide(newPosition, game->blocks))
        return;
    if(game->player->willCollide(newPosition, game->enemies))
        return;

    // jezeli nie bedzie kolidowal, moze sie przesunac
    game->player->moveDown();

    // jezeli gracz dotknal krawedzi, a nie jest na koncu planszy, nalezy "przesunac ekran"
    if(game->player->getTouchedEdge() == Down)
    {
        if(game->gameWindow->getPos().y - STEP >= SCREEN_HEIGHT - game->gameWindow->getBoardH())
            simulatingNotMoveElementsDown(game);
    }
}

void executingMoveLeft(Game* game)
{
    math_vector newPosition = {game->player->getPos().x - (float)STEP, game->player->getPos().y};
    // zakoncz, jezeli gracz w nowej pozycji kolidowalby z ktorymkolwiek z blokow, przeciwnikow,
    if(game->player->willCollide(newPosition, game->blocks))
        return;
    if(game->player->willCollide(newPosition, game->enemies))
        return;

    // jezeli nie bedzie kolidowal, moze sie przesunac
    game->player->moveLeft();

    // jezeli gracz dotknal krawedzi, a nie jest na koncu planszy, nalezy "przesunac ekran"
    if(game->player->getTouchedEdge() == Left)
    {
        if(game->gameWindow->getPos().x + STEP <= 0.0)
            simulatingNotMoveElementsLeft(game);
    }
}

void executingMoveRight(Game* game)
{
    math_vector newPosition = {game->player->getPos().x + (float)STEP, game->player->getPos().y};
    // zakoncz, jezeli gracz w nowej pozycji kolidowalby z ktorymkolwiek z blokow, przeciwnikow,
    if(game->player->willCollide(newPosition, game->blocks))
        return;
    if(game->player->willCollide(newPosition, game->enemies))
        return;

    // jezeli nie bedzie kolidowal, moze sie przesunac
    game->player->moveRight();

    // jezeli gracz dotknal krawedzi, a nie jest na koncu planszy, nalezy "przesunac ekran"
    if(game->player->getTouchedEdge() == Right)
    {
        if(game->gameWindow->getPos().x - STEP >= SCREEN_WIDTH - game->gameWindow->getBoardW())
            simulatingNotMoveElementsRight(game);
    }
}





void simulatingNotMoveElementsUp(Game* game) {
    // symulowanie nieprzesuwania tla
    game->gameWindow->setPos(game->gameWindow->getPos().x,
                             game->gameWindow->getPos().y + STEP);
    // .._.. blokow
    for (int i = 0; i < game->blocks.size(); i++){
        game->blocks[i]->setPos(game->blocks[i]->getPos().x, game->blocks[i]->getPos().y + STEP);
    }
    // .._.. wrogow
    for (int i = 0; i < game->enemies.size(); i++){
        game->enemies[i]->setPos(game->enemies[i]->getPos().x, game->enemies[i]->getPos().y + STEP);
    }
    // .._.. bonusHealth
    game->health->setPos(game->health->getPos().x,
                             game->health->getPos().y + STEP);
    // .._.. highlight'ow
    simulatingNotMoveListUp(game->highlights, Directions::up);

    // .._.. pociskow
    simulatingNotMoveListUp(game->bullets, Directions::up);
}

void simulatingNotMoveElementsDown(Game* game) {
    // symulowanie nieprzesuwania tla
    game->gameWindow->setPos(game->gameWindow->getPos().x,
                             game->gameWindow->getPos().y - STEP);
    // .._.. blokow
    for (int i = 0; i < game->blocks.size(); i++){
        game->blocks[i]->setPos(game->blocks[i]->getPos().x, game->blocks[i]->getPos().y - STEP);
    }
    // .._.. przeciwnikow
    for (int i = 0; i < game->enemies.size(); i++){
        game->enemies[i]->setPos(game->enemies[i]->getPos().x, game->enemies[i]->getPos().y - STEP);
    }
    // .._.. bonusHealth
    game->health->setPos(game->health->getPos().x,
                             game->health->getPos().y - STEP);
    // .._.. highlight'ow
    simulatingNotMoveListUp(game->highlights, Directions::down);

    // .._.. pociskow
    simulatingNotMoveListUp(game->bullets, Directions::down);

}

void simulatingNotMoveElementsLeft(Game* game) {
    // symulowanie nieprzesuwania tla
    game->gameWindow->setPos(game->gameWindow->getPos().x + STEP,
                             game->gameWindow->getPos().y);
    // .._.. blokow
    for (int i = 0; i < game->blocks.size(); i++){
        game->blocks[i]->setPos(game->blocks[i]->getPos().x + STEP, game->blocks[i]->getPos().y);
    }
    // .._.. przeciwnikow
    for (int i = 0; i < game->enemies.size(); i++){
        game->enemies[i]->setPos(game->enemies[i]->getPos().x + STEP, game->enemies[i]->getPos().y);
    }
    // .._.. bonusHealth
    game->health->setPos(game->health->getPos().x + STEP,
                             game->health->getPos().y);
    // .._.. highlight'ow
    simulatingNotMoveListUp(game->highlights, Directions::left);

    // .._.. pociskow
    simulatingNotMoveListUp(game->bullets, Directions::left);
}

void simulatingNotMoveElementsRight(Game* game) {
    // symulowanie nieprzesuwania tla
    game->gameWindow->setPos(game->gameWindow->getPos().x - STEP,
                             game->gameWindow->getPos().y);
    // .._.. blokow
    for (int i = 0; i < game->blocks.size(); i++){
        game->blocks[i]->setPos(game->blocks[i]->getPos().x - STEP, game->blocks[i]->getPos().y);
    }
    // .._.. przeciwnikow
    for(int i = 0; i < game->enemies.size(); i++){
        game->enemies[i]->setPos(game->enemies[i]->getPos().x - STEP, game->enemies[i]->getPos().y);
    }
    // .._.. bonusHealth
    game->health->setPos(game->health->getPos().x - STEP,
                             game->health->getPos().y);
    // .._.. highlight'ow
    simulatingNotMoveListUp(game->highlights, Directions::right);

    // .._.. pociskow
    simulatingNotMoveListUp(game->bullets, Directions::right);
}