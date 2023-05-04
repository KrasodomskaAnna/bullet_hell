#include "game.h"
#include "config.h"

Game::Game() {
    // tworzenie "okienka" gry o zadanym tytule i wymiarach
    this->gameWindow = new GameWindow("Bullet Hell 188863", SCREEN_WIDTH, SCREEN_HEIGHT);
    // ladowanie grafiki gry
    this->backgroundTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/bg.bmp"));
    this->endScreenTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/end.bmp"));
    this->menuScreenTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/menu.bmp"));
    this->winScreenTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/win.bmp"));
    this->winAllScreenTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/winall.bmp"));
    this->savingScreenTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/save.bmp"));
    this->scoreBoardScreenTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/scoreboard.bmp"));

    this->charsetTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/cs8x8.bmp"));
    this->lifebarTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/lifebar.bmp"));

    this->plusTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/plus.bmp"));
    this->minusTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/minus.bmp"));

    this->barTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/bar.bmp"));
    this->blockTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/asteroida.bmp"));
    this->boomBlockTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/boom.bmp"));

    this->enemyTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/enemy_2.bmp"));
    this->animationEnemyTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/enemy_animation2.bmp"));
    this->bulletTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/bullet.bmp"));
    this->greaterBulletTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/greaterbullet.bmp"));
    this->fireworkTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/firework.bmp"));
    this->playerBulletTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/playerbullet.bmp"));

    this->squareHighlightTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/kwadrat.bmp"));
    this->rectangleHorizontalHighlightTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/horizontal.bmp"));
    this->rectangleVerticalHighlightTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/vertical.bmp"));

    this->buttonTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/button.bmp"));
    this->clickedButtonTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/button_clicked.bmp"));

    this->bonusHealthTexture = SDL_CreateTextureFromSurface(this->gameWindow->getRenderer(), SDL_LoadBMP("./resources/health.bmp"));


    this->gameWindow->setBgDimensions(this->backgroundTexture);

    this->player = new Player(this->gameWindow, "./resources/eti.bmp", "./resources/eti2.bmp");

    this->menu = new Menu(buttonTexture, clickedButtonTexture);
    this->health = new Health(this->gameWindow, bonusHealthTexture);

    this->playerName = new char[MAX_PLAYER_NAME_LENGTH]();
}

void Game::reset() {
    this->levelTimeElapsed = 0;
    this->gameState = GameState::gameScreen;
    this->loadLevel();
    this->player->setHealth(100);
    this->points = 0;
}

void Game::nextLevel() {
    this->points = 0;
    this->playerHit = 0;
    this->playerShoot = 0;
    this->levelTimeElapsed = 0;
    this->gameState = GameState::gameScreen;
    this->level += 1;
    if(this->level > 4) {
        this->level -= 1;
        this->gameState = GameState::winAllScreen;
        return;
    }
    this->loadLevel();
    this->player->setHealth(100);
}

void Game::updateMenu() {
    switch(menu->inputState) {
        case MenuInputState::up:
            if(menu->activeButtonIndex > 0)
                menu->activeButtonIndex -= 1;
            menu->updateButtonsTextures();
            break;
        case MenuInputState::down:
            if(menu->activeButtonIndex < menu->buttons.size() - 1)
                menu->activeButtonIndex += 1;
            menu->updateButtonsTextures();
            break;
        case MenuInputState::click:
            if (menu->activeButtonIndex == 5) {
                this->loadScoreboard();
                this->gameState = GameState::scoreBoardScreen;
                break;
            }  
            if(menu->activeButtonIndex == 6)
                gameRunning = false;
            else {
                level = menu->activeButtonIndex;
                reset();
            }
            break;
        default:
            break;
    }
}

void Game::loadScoreboard() {
    Highscore* highscore = new Highscore("highscore.txt");
    this->scoreBoard = highscore->getHighscores();
    delete(highscore);
}

void Game::loadLevel() {
    // przesuniecie tla na wlasciwa pozycje
    gameWindow->setPos(CORD_ORIGIN,
                       CORD_ORIGIN);
    // zwalnianie pamieci poprzez usuwanie blokow
    for (int i = 0; i < blocks.size(); i++) {
        delete blocks[i];
    }
    blocks.clear();
    // .._.. przeciwnikow
    for (int i = 0; i < enemies.size(); i++) {
        delete enemies[i];
    }
    enemies.clear();
    // .._.. highlight'ow
    highlights.deleteAll();
    // .._.. pociskow
    bullets.deleteAll();
    // ustawianie gracza na srodku ekranu
    player->setPos((float) (SCREEN_WIDTH - player->currentFrame.w) / 2,
                   (float) (SCREEN_HEIGHT - player->currentFrame.h) / 2);

    // w zalezności od levelu ustawiane sa nowe bloki i nowi przeciwnicy
    auto config = new Config(
    "./config.txt",
    this->level,
    &this->advancedAttackFrequency, &this->blocks, &this->enemies, this->gameWindow, this->enemyTexture, this->animationEnemyTexture,
    &this->bullets, this->bulletTexture, this->blockTexture);
    config->load();
    delete(config);
}

Game::~Game() {
    delete(menu);
    delete(player);
    delete[](playerName);
    delete(scoreBoard);
    delete(gameWindow);
    delete(health);

    gameWindow->cleanUp();

    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(endScreenTexture);
    SDL_DestroyTexture(menuScreenTexture);
    SDL_DestroyTexture(winScreenTexture);
    SDL_DestroyTexture(winAllScreenTexture);
    SDL_DestroyTexture(savingScreenTexture);
    SDL_DestroyTexture(scoreBoardScreenTexture);

    SDL_DestroyTexture(buttonTexture);
    SDL_DestroyTexture(clickedButtonTexture);

    SDL_DestroyTexture(charsetTexture);

    SDL_DestroyTexture(lifebarTexture);
    SDL_DestroyTexture(barTexture);

    SDL_DestroyTexture(plusTexture);
    SDL_DestroyTexture(minusTexture);

    SDL_DestroyTexture(blockTexture);
    SDL_DestroyTexture(boomBlockTexture);
    SDL_DestroyTexture(enemyTexture);
    SDL_DestroyTexture(animationEnemyTexture);
    SDL_DestroyTexture(bulletTexture);
    SDL_DestroyTexture(greaterBulletTexture);
    SDL_DestroyTexture(fireworkTexture);
    SDL_DestroyTexture(playerBulletTexture);

    SDL_DestroyTexture(squareHighlightTexture);
    SDL_DestroyTexture(rectangleHorizontalHighlightTexture);
    SDL_DestroyTexture(rectangleVerticalHighlightTexture);

    SDL_DestroyTexture(bonusHealthTexture);
}
