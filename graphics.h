#ifndef BULLET_HELL_5_GRAPHICS_H
#define BULLET_HELL_5_GRAPHICS_H
#pragma once
#include "game.h"
#include "const.h"

// w zalezności od stanu gry (gameState) uruchamia odpowiednia funkcje renderujace grafike gry (nizej)
void graphics(Game* game);

void gameGraphics(Game* game);
void menuGraphics(Game* game);
void saveGraphics(Game* game);
void scoreBoardGraphics(Game* game);
void displayOneTextureGraphics(Game* game, SDL_Texture* texture);

void renderHighlights(Game* game);
void renderBullets(Game* game);
void renderGameInformation(Game* game);


#endif //BULLET_HELL_5_GRAPHICS_H
