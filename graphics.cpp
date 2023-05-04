#include "graphics.h"

void graphics(Game *game)
{
    // wyczyszczenie "pamieci" rendera, czyli wszystkich wyswietlanych elementow
    game->gameWindow->clear();

    // wyswietlenie odpowiedniej grafiki
    switch (game->gameState)
    {
    case GameState::gameScreen:
        gameGraphics(game);
        break;
    case GameState::menuScreen:
        menuGraphics(game);
        break;
    case GameState::endScreen:
        displayOneTextureGraphics(game, game->endScreenTexture);
        break;
    case GameState::winScreen:
        displayOneTextureGraphics(game, game->winScreenTexture);
        break;
    case GameState::winAllScreen:
        displayOneTextureGraphics(game, game->winAllScreenTexture);
        break;
    case GameState::savingScreen:
        saveGraphics(game);
        break;
    case GameState::scoreBoardScreen:
        scoreBoardGraphics(game);
        break;
    default:
        break;
    }

    // renderowanie wszytkich elementow przekazanych do rendera w oknie gry
    game->gameWindow->display();
}

void gameGraphics(Game *game)
{
    // render tla
    game->gameWindow->render(game->gameWindow->getPos().x, game->gameWindow->getPos().y, game->backgroundTexture, game->gameWindow->getBoardW(), game->gameWindow->getBoardH(), NO_SCALE, NO_SCALE);
    // .._.. gracza
    game->gameWindow->render(game->player->getPos().x, game->player->getPos().y, game->player->texture);
    // .._.. blokow
    for (int i = 0; i < game->blocks.size(); i++)
    {
        game->gameWindow->render(game->blocks[i]->getPos().x, game->blocks[i]->getPos().y, game->blocks[i]->texture); //game->blocks[i]->texture);
    }
    // .._.. przeciwnikow
    for (int i = 0; i < game->enemies.size(); i++)
    {
        game->gameWindow->render(game->enemies[i]->getPos().x, game->enemies[i]->getPos().y, game->enemies[i]->texture);
    }
    // .._.. bonusHealth
    if (game->health->isDisplay)
        game->gameWindow->render(game->health->getPos().x, game->health->getPos().y, game->health->texture);
    // .._.. highlit'ow
    renderHighlights(game);
    // .._.. pociskow
    renderBullets(game);

    // .._.. informacji dotyczacych gry
    renderGameInformation(game);
}

void menuGraphics(Game *game)
{
    game->gameWindow->render(CORD_ORIGIN, CORD_ORIGIN, game->menuScreenTexture);
    float deltaX = 15;
    float deltaY = 7.7;
    for (int i = 0; i < game->menu->buttons.size(); i++)
    {
        game->gameWindow->render(game->menu->buttons[i]->getPos().x, game->menu->buttons[i]->getPos().y, game->menu->buttons[i]->texture);
        game->gameWindow->drawText(game->menu->buttons[i]->getPos().x + deltaX, game->menu->buttons[i]->getPos().y + deltaY, game->menu->buttons[i]->text, game->charsetTexture, NO_SCALE * 2);
    }
}

void displayOneTextureGraphics(Game *game, SDL_Texture *texture)
{
    game->gameWindow->render(CORD_ORIGIN, CORD_ORIGIN, texture);
}

void renderHighlights(Game *game)
{
    // jezeli nie istnieje jakikolwiek highlight
    if (game->highlights.head == nullptr)
        return;

    node<Highlight *> *current = game->highlights.getNext(nullptr);
    while (current != nullptr)
    {
        if (current->value->shape == Shape::square)
            game->gameWindow->render(current->value->getPos().x, current->value->getPos().y, game->squareHighlightTexture);
        if (current->value->shape == Shape::rectangleH)
            game->gameWindow->render(current->value->getPos().x, current->value->getPos().y, game->rectangleHorizontalHighlightTexture);
        else
            game->gameWindow->render(current->value->getPos().x, current->value->getPos().y, game->rectangleVerticalHighlightTexture);
        current = current->next;
    }
}

void renderBullets(Game *game)
{
    // jezeli nie istnieje jakikolwiek highlight
    if (game->bullets.head == nullptr)
        return;

    node<Bullet *> *current = game->bullets.getNext(nullptr);
    while (current != nullptr)
    {
        game->gameWindow->render(current->value->getPos().x, current->value->getPos().y, current->value->texture, current->value->getAngle());
        current = current->next;
    }
}

void renderGameInformation(Game *game)
{
    // wyrysowanie czasu, ktory uplynal od poczatku levelu
    char buffer[40];
    sprintf(buffer, "Time elapsed: %ds", (game->levelTimeElapsed) / 1000);
    game->gameWindow->drawText(RELATIVE_POS_TIME_ELAPSED_X, RELATIVE_POS_TIME_ELAPSED_Y, buffer, game->charsetTexture, NO_SCALE * 1.4);

    sprintf(buffer, "level: %d score %d", game->level, game->points);
    game->gameWindow->drawText(RELATIVE_POS_LEVEL_X, RELATIVE_POS_LEVEL_Y, buffer, game->charsetTexture, NO_SCALE * 2);
    if (game->timeAnimationStart != 0 && game->timeAnimationStart + POINTS_CHANGE_ANIMATION > SDL_GetTicks())
    {
        float scale = (SDL_GetTicks() - game->timeAnimationStart) * POINTS_SIZE_ANIMATION_SCALE * POINTS_CHANGE_ANIMATION_SCALE;
        game->gameWindow->render(POINTS_CHANGE_X, POINTS_CHANGE_Y, game->isPlus ? game->plusTexture : game->minusTexture, scale, scale);
    }

    game->gameWindow->drawText(RELATIVE_POS_STRING_LIFE_X, RELATIVE_POS_LIFE_VIEW_Y, "Lifebar:", game->charsetTexture, NO_SCALE * 1.2);
    game->gameWindow->render(RELATIVE_POS_LIFEBAR_X - 3, RELATIVE_POS_LIFE_VIEW_Y - 3, game->barTexture, 1, 1);
    game->gameWindow->render(RELATIVE_POS_LIFEBAR_X, RELATIVE_POS_LIFE_VIEW_Y, game->lifebarTexture, game->player->getHealth() / 10, 1);

    sprintf(buffer, "%d", game->player->getHealth());
    game->gameWindow->drawText(RELATIVE_POS_LIFEBAR_X + 35, RELATIVE_POS_LIFE_VIEW_Y, buffer, game->charsetTexture, NO_SCALE * 1.3);
}

void saveGraphics(Game *game)
{
    game->gameWindow->render(CORD_ORIGIN, CORD_ORIGIN, game->savingScreenTexture);
    game->gameWindow->drawText(RELATIVE_POS_NAME_X, RELATIVE_POS_NAME_Y, game->playerName, game->charsetTexture, NO_SCALE * 1.2);
}

void scoreBoardGraphics(Game *game)
{
    game->gameWindow->render(CORD_ORIGIN, CORD_ORIGIN, game->scoreBoardScreenTexture);
    float offset = 260;
    for (int i = game->scoreBoardCursor; i < game->scoreBoardCursor + 5 && i < game->scoreBoard->size(); i++)
    {
        char buffer[MAX_PLAYER_NAME_LENGTH + 53];
        sprintf(buffer, "%d %s points: %d level: %d", i, (*game->scoreBoard)[i].username, (*game->scoreBoard)[i].score, (*game->scoreBoard)[i].level);
        game->gameWindow->drawText(RELATIVE_POS_SCORES_DISPLAY_X, offset, buffer, game->charsetTexture, NO_SCALE * 2);
        offset += DELTA_SCORES_DISPLAY_POSITION_Y;
    }
}