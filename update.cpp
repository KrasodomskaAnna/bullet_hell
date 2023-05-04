#include "update.h"

void update(Game *game) {
    updateEnemies(game);
    updateHighlights(game);
    updateBonusHealth(game);

    // jezeli gracz nacisnal przycisk z klawiatury nalezy wykonac odpowiadajaca mu akcje
    if (game->inputState.up)
        executingMoveUp(game);
    if (game->inputState.down)
        executingMoveDown(game);
    if (game->inputState.right)
        executingMoveRight(game);
    if (game->inputState.left)
        executingMoveLeft(game);
    if (game->inputState.o)
        playerShoot(game);

    updateBullets(game);
    clearStaleBlocks(game);
    updateConditions(game);
}

float updateAngle(float bulletX, float bulletY, float pointX, float pointY) {
    float b = bulletX - pointX;
    float a = bulletY - pointY;
    float tan = a / b;
    if (a >= 0) {
        if (b >= 0)
            return atanf(tan) * ((FULL_CIRCLE/2) / PI) + (FULL_CIRCLE/2); // jezeli jest z drugiej cwiartki
        else
            return atanf(tan) * ((FULL_CIRCLE/2) / PI); // jezeli jest z pierwszej cwiartki
    }
    else {
        if (b >= 0)
            return atanf(tan) * ((FULL_CIRCLE/2) / PI) + (FULL_CIRCLE/2); // jezeli jest z trzeciej cwiartki
        else
            return atanf(tan) * ((FULL_CIRCLE/2) / PI); // jezeli jest z czwartej cwiartki
    }
}

void updateEnemies(Game *game) {
    enemiesStrikes(game);
    enemiesMove(game);
}

void enemiesStrikes(Game *game) {
    for (int i = 0; i < game->enemies.size(); i++)
    {
        if ((int)game->levelTimeElapsed % ((i + 1) * 1000) < 5)
        {
            float bulletX = game->enemies[i]->getMiddlePos().x;
            float bulletY = game->enemies[i]->getMiddlePos().y;
            float playerX = game->player->getMiddlePos().x;
            float playerY = game->player->getMiddlePos().y;
            game->enemies[i]->shoot(random(MIN_BULLET_SPEED, MAX_BULLET_SPEED), updateAngle(bulletX, bulletY, playerX, playerY));
        }
        if (SDL_GetTicks() - game->advancedAttackLast >= game->advancedAttackFrequency)
        {
            game->advancedAttackLast = SDL_GetTicks();
            switch ((int)random(0, 3))
            {
            case 0:
                chooseHighlightShape(game);
                break;
            case 1:
                firework(game, i);
                break;
            default:
                float bulletX = game->enemies[i]->getMiddlePos().x;
                float bulletY = game->enemies[i]->getMiddlePos().y;
                float playerX = game->player->getMiddlePos().x;
                float playerY = game->player->getMiddlePos().y;
                game->bullets.addAfter(new Bullet({bulletX, bulletY}, game->greaterBulletTexture, random(MIN_GREATER_BULLET_SPEED, MAX_GREATER_BULLET_SPEED), updateAngle(bulletX, bulletY, playerX, playerY), BulletType::greater));
                break;
            }
        }
    }
}

void enemiesMove(Game *game) {
    if ((int)game->levelTimeElapsed % 1000 < 50)
    {
        for (int i = 0; i < game->enemies.size(); i++)
        {
            if (game->enemies[i]->getType() == EnemyType::any)
            {
                int j = (int)random(0, 4);
                switch (j % 4)
                {
                case 0:
                    executingMoveUpEnemy(game, i);
                    break;
                case 1:
                    executingMoveDownEnemy(game, i);
                    break;
                case 2:
                    executingMoveRightEnemy(game, i);
                    break;
                default:
                    executingMoveLeftEnemy(game, i);
                    break;
                }
            }
        }
    }
}

void chooseHighlightShape(Game *game) {
    if (randomChoice())
        game->highlights.addAfter(new Highlight(game->squareHighlightTexture, Shape::square,
                                                game->gameWindow->getBoardW(), game->gameWindow->getBoardH()));
    else
    {
        auto horizontal = new Highlight(game->rectangleHorizontalHighlightTexture, Shape::rectangleH,
                                        game->gameWindow->getBoardW(), game->gameWindow->getBoardH());
        game->highlights.addAfter(horizontal);
        auto vertical = new Highlight(game->rectangleVerticalHighlightTexture, Shape::rectangleV);
        vertical->setPos(horizontal->getPos().x + horizontal->currentFrame.w / 2.0 - vertical->currentFrame.w / 2.0, horizontal->getPos().y + horizontal->currentFrame.h / 2.0 - vertical->currentFrame.h / 2.0);
        game->highlights.addAfter(vertical);
    }
}

void updateHighlights(Game *game) {
    // jezeli nie istnieje jakikolwiek highlight
    if (game->highlights.head == nullptr) return;

    node<Highlight *> *current = game->highlights.getNext(nullptr);
    while (current != nullptr)
    {
        // sprawdzenie czy minal czas istnienia, jezeli tak, usuwanie, jezeli nie ma nastepnego, wyjdz
        if (SDL_GetTicks() - current->value->getCreationTime() >= MAX_TIME_HIGHLIGHT_ALIVE) {
            node<Highlight *> *next = current->next;
            highlightsStrike(game, current->value);
            game->highlights.remove(current);
            current = next;
            continue;
        }
        current = current->next;
    }
}

void highlightsStrike(Game *game, Highlight *highlight) {
    if (game->player->willCollide(game->player->getPos(), highlight))
        playerHit(game, Hitboxes::all);
    for (int i = 0; i < game->enemies.size(); i++) {
        if (game->enemies[i]->willCollide(game->enemies[i]->getPos(), highlight))
            enemyHit(game, i, Hitboxes::all);
    }
}

void firework(Game *game, int index) {
    float bulletX = game->enemies[index]->getMiddlePos().x;
    float bulletY = game->enemies[index]->getMiddlePos().y;
    float playerX = game->player->getMiddlePos().x;
    float playerY = game->player->getMiddlePos().y;
    game->bullets.addAfter(new Bullet({bulletX, bulletY}, game->fireworkTexture, random(MIN_BULLET_SPEED, MAX_BULLET_SPEED), updateAngle(bulletX, bulletY, playerX, playerY), BulletType::firework));
}

void updateBonusHealth(Game *game) {
    // wyswietlenie bonusHealth na planszy
    if (randomChoice() && !game->health->isDisplay) placeBonusHealth(game);

    // jezeli jest wyswietlony, a gracz wszedl w niego -> zwiekszenie zycia gracza
    if (game->health->isDisplay) {
        if (game->player->willCollide(game->player->getPos(), game->health)) {
            game->player->setHealth(game->player->getHealth() + GIVEN_LIFE_PERCENT);
            // jezeli gracz ma 100% zycia, nie zwiekszaj bardziej
            if (game->player->getHealth() > 100)
                game->player->setHealth(100);
            game->health->hide();
        }
    }

    // jezeli wyswietla sie ponad mozliwy zdefiniowany czas, nalezy go schowac
    if (SDL_GetTicks() - game->health->getStartTime() >= MAX_TIME_BONUS_HEALTH_DISPLAY)
        game->health->hide();
}

void placeBonusHealth(Game *game) {
    // szukanie pozycji, w ktorej bonusHealth z niczym nie koliduje
    bool collide = true;
    while (collide)
    {
        game->health->setPos(random(game->gameWindow->getPos().x, game->gameWindow->getPos().x + game->gameWindow->getBoardW() - game->health->currentFrame.w), random(game->gameWindow->getPos().y, game->gameWindow->getPos().y + game->gameWindow->getBoardH() - game->health->currentFrame.h));
        // jezeli niekoliduje, sprawdzenie kolejnych warunkow
        if (!game->health->willCollide(game->health->getPos(), game->player))
        {
            bool collideWithEnemies = false;
            for (int i = 0; i < game->enemies.size(); i++) {
                if (game->health->willCollide(game->health->getPos(), game->enemies[i]))
                    collideWithEnemies = true;
            }
            if (!collideWithEnemies) {
                bool collideWithBlocks = false;
                for (int i = 0; i < game->blocks.size(); i++) {
                    if (game->health->willCollide(game->health->getPos(), game->blocks[i]))
                        collideWithBlocks = true;
                }
                if (!collideWithBlocks)
                    collide = false;
            }
        }
    }
    game->health->display();
}

void updateBullets(Game *game) {
    bulletsStop(game);
    bulletsStrikes(game);
}

bool checkBulletEnemyCollision(Game *game, node<Bullet *> *current) {
    for (int i = 0; i < game->enemies.size(); i++)
    {
        Hitboxes enemyCollision = game->enemies[i]->willCollideHitboxes(game->enemies[i]->getPos(), current->value);
        // jezeli koliduje z pociskiem
        if (enemyCollision != Hitboxes::none) {
            float delta = getDeltaHitbox(enemyCollision);
            game->playerShoot += 1;
            game->playerHit = 0;
            game->points += ceil(GIVE_POINTS * delta * game->playerShoot);
            game->enemies[i]->setHealth(game->enemies[i]->getHealth() - TAKEN_LIFE_PERCENT * delta);
            // jezeli enemy skonczyło sie zycie, usun
            if (game->enemies[i]->getHealth() <= 0)
                game->enemies.deleteAt(i);
            game->timeAnimationStart = SDL_GetTicks();
            game->isPlus = true;
            return true;
        }
    }

    return false;
}

void bulletsStrikes(Game *game) {
    if (game->bullets.head == nullptr) return; // jezeli nie istnieje jakikolwiek pocisk

    node<Bullet *> *current = game->bullets.getNext(nullptr);
    while (current != nullptr) {
        // jezeli bullet jest firework'iem, "leci ponad plansze", wiec nie sprawdza sie kolizji
        if (current->value->type == BulletType::firework) {
            current = current->next;
            continue;
        }
        // sprawdzenie czy wpadlo w przeszkode; sprawdzenie czy moglo zabic gracza; sprawdzenie bullet moze zabijac przeciwnika (jest wystrzelony od player'a) i koliduje z ktoryms z przeciwnikow
        bool shootBlock = false;
        for (int i = 0; i < game->blocks.size(); i++) {
            if(shootBlock) continue;
            if (current->value->willCollide(game->blocks)) {
                game->blocks[i]->texture = game->boomBlockTexture;
                game->blocks[i]->destroyedAt = SDL_GetTicks();
                node<Bullet *> *next = current->next;
                game->bullets.remove(current);
                current = next;
                shootBlock = true;
            }
        }
        if(shootBlock) continue;

        Hitboxes playerCollision = game->player->willCollideHitboxes(game->player->getPos(), current->value);
        if (playerCollision != Hitboxes::none && current->value->type != BulletType::player) {
            playerHit(game, playerCollision);
            node<Bullet *> *next = current->next;
            game->bullets.remove(current);
            current = next;
            continue;
        }

        if (current->value->type == BulletType::player && checkBulletEnemyCollision(game, current)) {
            node<Bullet *> *next = current->next;
            game->bullets.remove(current);
            current = next;
            continue;
        }

        current = current->next;
    }
}

void bulletsStop(Game *game) {
    if (game->bullets.head == nullptr) return; // jezeli nie istnieje jakikolwiek pocisk

    node<Bullet *> *current = game->bullets.getNext(nullptr);
    while (current != nullptr)
    {
        // usuń, jeżeli wyhamował, jezeli nie ma nastepnego -> wyjdz
        if (current->value->update())
        {
            if (current->value->type == BulletType::firework) {
                float angle = 0;
                while (angle <= FULL_CIRCLE) {
                    game->bullets.addAfter(new Bullet({current->value->getPos().x + ((float)current->value->currentFrame.w / 2), current->value->getPos().y + ((float)current->value->currentFrame.h / 2)}, game->bulletTexture, random(MIN_SHARD_SPEED, MAX_SHARD_SPEED), angle, BulletType::shard));
                    angle += FIREWORK_DELTA_ANGLE;
                }
            }
            node<Bullet *> *next = current->next;
            game->bullets.remove(current);
            current = next;
            continue;
        }
        current = current->next;
    }
}

void playerHit(Game *game, Hitboxes hitbox) {
    if (SDL_GetTicks() - game->player->hitTime >= INVINCIBILITY_TIME) { // jezeli minal czas niesmiertelnosci playera
        float delta = getDeltaHitbox(hitbox);
        game->player->setHealth(game->player->getHealth() - TAKEN_LIFE_PERCENT * delta); // zmniejszenie zycia gracza, jezeli skonczyło sie -> koniec gry
        if (game->player->getHealth() <= 0)
            game->gameState = GameState::endScreen;
        game->player->hitTime = SDL_GetTicks();
        game->playerHit += 1;
        game->playerShoot = 0;
        game->points -= ceil((TAKE_POINTS * delta) * game->playerHit);
        game->timeAnimationStart = SDL_GetTicks();
        game->isPlus = false;
    }
}

void enemyHit(Game *game, int index, Hitboxes hitbox) {
    float delta = getDeltaHitbox(hitbox);
    // zmniejszenie zycia przeciwnika
    game->enemies[index]->setHealth(game->enemies[index]->getHealth() - TAKEN_LIFE_PERCENT * delta);
}

float getDeltaHitbox(Hitboxes hitbox) {
    switch (hitbox)
    {
    case Hitboxes::all:
        return ALL_HITBOX;
    case Hitboxes::head:
        return HEAD_HITBOX;
    case Hitboxes::torso:
        return TORSO_HITBOX;
    case Hitboxes::legs:
        return LEGS_HITBOX;
    default:
        return 0;
    }
}

void playerShoot(Game *game) {
    game->bullets.addAfter(new Bullet(game->player->getMiddlePos(), game->playerBulletTexture, random(MIN_BULLET_SPEED, MAX_BULLET_SPEED), 0, BulletType::player));
}



void clearStaleBlocks(Game* game) {
    for (int i = 0; i < game->blocks.size(); i++) {
        if(game->blocks[i]->destroyedAt != 0 && game->blocks[i]->destroyedAt + BLOCK_EXPLOSION_ANIMATION_TIME < SDL_GetTicks())
            game->blocks.deleteAt(i);
    }
}




void updateConditions(Game* game) {
    // jezeli nie ma przeciwnikow, wyswietl wygrana levelu; jezeli gracz wygral ostatni level -> wyswietl koniec gry (winAll)
    if (game->enemies.size() == 0) {
        if(game->level == 4) {
            game->gameState = GameState::winAllScreen;
            return;
        }
        game->gameState = GameState::winScreen;
    }
}