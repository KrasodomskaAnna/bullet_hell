#include "player.h"
#include "game.h"


Player::Player(GameWindow* gameWindow, const char* texturePath, const char* animationTexturePath) : Individual(gameWindow, nullptr,
                                                                                                               nullptr) {
    this->gameWindow = gameWindow;
    this->texture = SDL_CreateTextureFromSurface(gameWindow->getRenderer(), SDL_LoadBMP(texturePath));
    SDL_QueryTexture(this->texture, nullptr, nullptr, &this->currentFrame.w, &this->currentFrame.h);
    this->baseTexture = this->texture;
    this->animationTexture = SDL_CreateTextureFromSurface(gameWindow->getRenderer(), SDL_LoadBMP(animationTexturePath));
}

void Player::moveUp() {
    this->changeTexture();
    if(this->getPos().y - STEP >= CORD_ORIGIN){
        this->setPos(this->getPos().x, this->getPos().y - STEP);
        this->edge = None;
    }
    else
        this->edge = Up;
}

void Player::moveDown() {
    this->changeTexture();
    if(this->getPos().y + STEP <= SCREEN_HEIGHT - this->currentFrame.h){
        this->setPos(this->getPos().x, this->getPos().y + STEP);
        this->edge = None;
    }
    else
        this->edge = Down;
}

void Player::moveRight() {
    this->changeTexture();
    if(this->getPos().x + STEP <= SCREEN_WIDTH - this->currentFrame.w) {
        this->setPos(this->getPos().x + STEP, this->getPos().y);
        this->edge = None;
    }
    else
        this->edge = Right;
}

void Player::moveLeft() {
    this->changeTexture();
    if(this->getPos().x - STEP >= CORD_ORIGIN){
        this->setPos(this->getPos().x - STEP, this->getPos().y);
        this->edge = None;
    }
    else
        this->edge = Left;
}



