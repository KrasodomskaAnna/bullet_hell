#ifndef BULLET_HELL_2_GAME_H
#define BULLET_HELL_2_GAME_H
#pragma once
#include "const.h"
#include "game_window.h"
#include "player.h"
#include "block.h"
#include "vector.h"
#include "enemy.h"
#include "bullet.h"
#include "list.h"
#include "highlight.h"
#include "menu.h"
#include "health.h"
#include "highscore.h"

// zapis stanow gry
enum class GameState {
    winAllScreen,
    gameScreen,
    endScreen,
    menuScreen,
    winScreen,
    savingScreen,
    scoreBoardScreen
};

struct InputState {
    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;
    bool o = false;
};

// obiekt gry, przechowuje "wszystko" co nalezy do gry w celu latwego przechwytywania wartosci
class Game {
public:
    Game();
    // reguluje czy gra nadal trwa
    bool gameRunning = true;
    // przechowanie stanu gdy
    GameState gameState = GameState::menuScreen;

    // menu
    Menu* menu;
    void updateMenu();
    // input z klawiatury
    InputState inputState;


    void reset();
    void nextLevel();

    int points = 0;
    int playerHit = 0;
    int playerShoot = 0;

    char* playerName;

    // czasy
    uint32_t gameStartTime;
    uint32_t timeElapsed;
    uint32_t levelTimeElapsed;
    uint32_t advancedAttackLast;

    // funkcja ladująca ustawienia levelu
    void loadLevel();
    // przechowanie na ktorym levelu jest gracz
    int level = 0;

    int advancedAttackFrequency = DEFAULT_ADVANCED_ATTACK_FREQUENCY;

    int scoreBoardCursor = 0;
    Vector<ScoreBoardItem>* scoreBoard = nullptr;
    void loadScoreboard();

    // tekstury, pointery do ...
    // okno gry
    GameWindow* gameWindow;
    SDL_Texture* backgroundTexture;
    SDL_Texture* endScreenTexture;
    SDL_Texture* menuScreenTexture;
    SDL_Texture* winScreenTexture;
    SDL_Texture* winAllScreenTexture;
    SDL_Texture* savingScreenTexture;
    SDL_Texture* scoreBoardScreenTexture;

    // przycisk
    SDL_Texture* buttonTexture;
    SDL_Texture* clickedButtonTexture;

    // .._.. tekstury liter
    SDL_Texture* charsetTexture;

    //.._.. tekstury lifebara
    SDL_Texture* lifebarTexture;
    SDL_Texture* barTexture;

    // .._.. tekstur animacji punktow
    uint32_t timeAnimationStart = 0;
    bool isPlus = true;
    SDL_Texture* plusTexture;
    SDL_Texture* minusTexture;

    // .._.. gracza i jego tekstury
    Player* player = nullptr;
    // .._.. wektora bloków i tekstury, ktorą przyjmuje kazdy z blokow
    Vector<Block*> blocks;
    SDL_Texture* blockTexture;
    SDL_Texture* boomBlockTexture;
    // .._.. wektora wrogow i tekstury, ktorą przyjmuje kazdy z wrogow
    Vector<Enemy*> enemies;
    SDL_Texture* enemyTexture;
    SDL_Texture* animationEnemyTexture;
    // .._.. listy pociskow i tekstury, którą przyjmuje kazdy z pociskow
    List<Bullet*> bullets;
    SDL_Texture* bulletTexture;
    SDL_Texture* greaterBulletTexture;
    SDL_Texture* fireworkTexture;
    SDL_Texture* playerBulletTexture;
    // .._.. highlightShape'ów
    List<Highlight*> highlights;
    SDL_Texture* squareHighlightTexture;
    SDL_Texture* rectangleHorizontalHighlightTexture;
    SDL_Texture* rectangleVerticalHighlightTexture;

    // .._.. bonusHealth
    Health* health = nullptr;
    SDL_Texture* bonusHealthTexture;

    ~Game();
};


#endif //BULLET_HELL_2_GAME_H
