#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "const.h"
#include "game_window.h"
#include "game.h"
#include "update.h"
#include "graphics.h"
#include "input.h"
#include <time.h>

extern "C"
{
#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
}

#define FRAMES 60.0
#define MS_PER_UPDATE (1000.0 / FRAMES)

// main
#ifdef __cplusplus
extern "C"
#endif
    int
    main(int argc, char **argv)
{
    Game *game = new Game();
    game->gameStartTime = SDL_GetTicks();
    uint32_t previous = game->gameStartTime;
    game->timeElapsed = 0;
    uint32_t lag = 0.0;
    while (game->gameRunning)
    {
        uint32_t current = SDL_GetTicks();
        uint32_t elapsed = (current - previous);
        game->timeElapsed += elapsed;
        game->levelTimeElapsed += elapsed;
        previous = current;
        lag += elapsed;

        while (lag >= MS_PER_UPDATE)
        {
            updateInput(game);
            if (game->gameState == GameState::gameScreen)
                update(game);
            else
                game->updateMenu();
            lag -= MS_PER_UPDATE;
        }

        graphics(game);

        uint32_t frameTime = SDL_GetTicks() - current;
        if(MS_PER_UPDATE > frameTime)
            SDL_Delay(MS_PER_UPDATE - frameTime);
    }
    delete (game);
    SDL_Quit();
    return 0;
};
