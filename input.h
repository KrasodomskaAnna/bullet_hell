#ifndef BULLET_HELL_5_INPUT_H
#define BULLET_HELL_5_INPUT_H
#pragma once
#include <cstring>
#include "game.h"


// funkcja obsluguje zdarzenia wywolane z inputu klawiatury, wywoluje odpowiednie funkcje obslugujace szczegolny input z poszczegolnych stanow gry
void updateInput(Game* game);
// funckje obsluguja szczegolny input z klawiatury
void inputGame(Game* game, SDL_Event &event);
void inputMenu(Game* game, SDL_Event &event);
void inputEnd(Game* game, SDL_Event &event);
void inputWin(Game* game, SDL_Event &event);
void inputSave(Game* game, SDL_Event& event);
void inputScoreBoard(Game* game, SDL_Event& event);
void inputCommon(Game* game, SDL_Event &event);

void saveScore(Game* game);


#endif //BULLET_HELL_5_INPUT_H
