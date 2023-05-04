#ifndef BULLET_HELL_3_UPDATE_H
#define BULLET_HELL_3_UPDATE_H
#pragma once
#include "const.h"
#include "game.h"
#include "random.h"
#include "player_move.h"
#include "enemy_move.h"


// funkcja aktualizuje wartosci gry i jej parametrow, obsluguje komendy przekazywane poprzez klikniecia na klawiaturze
void update(Game* game);



// funkcja zwraca kat pod jakim powinien być wystrzelony pocisk aby trafic w obiekt
float updateAngle(float bulletX, float bulletY, float pointX, float pointY);



// funkcja obsluguje zdarzenia przeciwnikow -> strzelanie, ruch
void updateEnemies(Game* game);
void enemiesStrikes(Game* game);
void enemiesMove(Game* game);


// funkcja obsluguje zdarzenia highlight'ow
void updateHighlights(Game*game);
void highlightsStrike(Game* game, Highlight* highlight);
// funkcja wybiera shape highlight'a
void chooseHighlightShape(Game*game);


// funkcja obsluguje zdarzenia bonusHealth
void updateBonusHealth(Game* game);
void placeBonusHealth(Game* game);


// funkcja obsluguje usuwanie pociskow
void updateBullets(Game* game);
bool checkBulletEnemyCollision(Game *game, node<Bullet *> *current);
void bulletsStrikes(Game* game);
void bulletsStop(Game* game);
// funckja obsluguje wystrzelenie pocisku firework
void firework(Game*game, int index);


// funkcje obsluguja odpowiednio zdarzenie uderzenia pocisku w gracza, w przeciwnika
void playerHit(Game* game, Hitboxes hitbox);
void enemyHit(Game* game, int index, Hitboxes hitbox);
// funkcja zwraca wspolczynnik straty/zysku zycia/punktow
float getDeltaHitbox(Hitboxes hitbox);

// funkcja obluguje zdarzenie wystrzelenia przez gracza
void playerShoot(Game* game);


void clearStaleBlocks(Game* game);



// funckja sprawdza czy zostal spelniony warunek przejscia do kolejnego poziomu
void updateConditions(Game* game);


#endif //BULLET_HELL_3_UPDATE_H
