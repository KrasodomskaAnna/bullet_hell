#include "input.h"
#include "highscore.h"

void updateInput(Game* game) {
    // wyczysczenie ostatnich akcji (aby sie nie wykonywaly w nieskonczonosc)
    game->inputState.up = false;
    game->inputState.down = false;
    game->inputState.right = false;
    game->inputState.left = false;
    game->inputState.o = false;
    game->menu->inputState = MenuInputState::none;

    // odluga zdarzenia z klawiatury
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (game->gameState == GameState::gameScreen) inputGame(game, event);
        else if (game->gameState == GameState::menuScreen) inputMenu(game, event);
        else if(game->gameState == GameState::endScreen) inputEnd(game, event);
        else if(game->gameState == GameState::winScreen) inputWin(game, event);
        else if (game->gameState == GameState::savingScreen) inputSave(game, event);
        else if (game->gameState == GameState::scoreBoardScreen) inputScoreBoard(game, event);
        inputCommon(game, event);
    }
}

void inputGame(Game* game, SDL_Event &event) {
        switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_W:
                    case SDL_SCANCODE_UP:
                        game->inputState.up = true;
                        break;
                    case SDL_SCANCODE_S:
                    case SDL_SCANCODE_DOWN:
                        game->inputState.down = true;
                        break;
                    case SDL_SCANCODE_A:
                    case SDL_SCANCODE_LEFT:
                        game->inputState.left = true;
                        break;
                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        game->inputState.right = true;
                        break;
                    case SDL_SCANCODE_O:
                        game->inputState.o = true;
                        break;
                    default:
                        break;
                }
                break;
        };
}

void inputMenu(Game* game, SDL_Event &event) {
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    game->menu->inputState = MenuInputState::up;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    game->menu->inputState = MenuInputState::down;
                    break;
                case SDL_SCANCODE_RETURN:
                    game->menu->inputState = MenuInputState::click;
                    break;
                default:
                    break;
            }
            break;
    };
}

void inputEnd(Game* game, SDL_Event &event) {
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    game->reset();
                    break;
                default:
                    break;
            }
            break;
    };
}

void inputWin(Game* game, SDL_Event &event) {
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    game->nextLevel();
                    break;
                case SDL_SCANCODE_S:
                    game->gameState = GameState::savingScreen;
                    break;
                default:
                    break;
            }
            break;
    };
}

void inputSave(Game* game, SDL_Event& event) {
    if (strlen(game->playerName) >= MAX_PLAYER_NAME_LENGTH-1) return;
    switch (event.type) {
    case SDL_KEYDOWN:
        switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_BACKSPACE:
            if (strlen(game->playerName) == 0) return;
            game->playerName[strlen(game->playerName) - 1] = 0;
            break;
        case SDL_SCANCODE_RETURN:
            saveScore(game);
            game->gameState = GameState::menuScreen;
            break;
        case SDL_SCANCODE_A:
            strcat(game->playerName, "a");
            break;
        case SDL_SCANCODE_B:
            strcat(game->playerName, "b");
            break;
        case SDL_SCANCODE_C:
            strcat(game->playerName, "c");
            break;
        case SDL_SCANCODE_D:
            strcat(game->playerName, "d");
            break;
        case SDL_SCANCODE_E:
            strcat(game->playerName, "e");
            break;
        case SDL_SCANCODE_F:
            strcat(game->playerName, "f");
            break;
        case SDL_SCANCODE_G:
            strcat(game->playerName, "g");
            break;
        case SDL_SCANCODE_H:
            strcat(game->playerName, "h");
            break;
        case SDL_SCANCODE_I:
            strcat(game->playerName, "i");
            break;
        case SDL_SCANCODE_J:
            strcat(game->playerName, "j");
            break;
        case SDL_SCANCODE_K:
            strcat(game->playerName, "k");
            break;
        case SDL_SCANCODE_L:
            strcat(game->playerName, "l");
            break;
        case SDL_SCANCODE_M:
            strcat(game->playerName, "m");
            break;
        case SDL_SCANCODE_N:
            strcat(game->playerName, "n");
            break;
        case SDL_SCANCODE_O:
            strcat(game->playerName, "o");
            break;
        case SDL_SCANCODE_P:
            strcat(game->playerName, "p");
            break;
        case SDL_SCANCODE_R:
            strcat(game->playerName, "r");
            break;
        case SDL_SCANCODE_S:
            strcat(game->playerName, "s");
            break;
        case SDL_SCANCODE_T:
            strcat(game->playerName, "t");
            break;
        case SDL_SCANCODE_U:
            strcat(game->playerName, "u");
            break;
        case SDL_SCANCODE_W:
            strcat(game->playerName, "w");
            break;
        case SDL_SCANCODE_X:
            strcat(game->playerName, "x");
            break;
        case SDL_SCANCODE_Y:
            strcat(game->playerName, "y");
            break;
        case SDL_SCANCODE_Z:
            strcat(game->playerName, "z");
            break;
        default:
            break;
        }
        break;
    };
}

void inputScoreBoard(Game* game, SDL_Event& event) {
    switch (event.type) {
    case SDL_KEYDOWN:
        switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_W:
        case SDL_SCANCODE_UP:
            if (game->scoreBoardCursor > 0) game->scoreBoardCursor--;
            break;
        case SDL_SCANCODE_S:
        case SDL_SCANCODE_DOWN:
            if (game->scoreBoardCursor + 5 < game->scoreBoard->size()) game->scoreBoardCursor++;
            break;
        default:
            break;
        }
        break;
    };
}

void inputCommon(Game* game, SDL_Event &event) {
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_ESCAPE:
                    game->gameRunning = false;
                    break;
                case SDL_SCANCODE_N:
                    if (game->gameState == GameState::savingScreen) break;
                    game->gameState = GameState::menuScreen;
                    break;
                default:
                    break;
            }
            break;
        case SDL_QUIT:
            game->gameRunning = false;
            break;
    };
}

void saveScore(Game* game) {
    Highscore* highscore = new Highscore("highscore.txt");
    highscore->updateHighscore(game->playerName, game->points, game->level);
    delete(highscore);
}