#ifndef BULLET_HELL_5_MENU_H
#define BULLET_HELL_5_MENU_H
#pragma once
#include "const.h"
#include "entity.h"
#include "vector.h"

enum class MenuInputState {
    none,
    up,
    down,
    click
};

class Button : public Entity {
public:
    Button(const char* text, SDL_Texture* texture, math_vector position) : Entity(texture) {
        this->text = text;
        this->texture = texture;
        this->setPos(position.x, position.y);
    }
    const char* text;
};

class Menu {
public:
    Menu(SDL_Texture* buttonTexture, SDL_Texture* clickedButtonTexture);
    Vector<Button*> buttons;
    MenuInputState inputState = MenuInputState::none;
    void updateButtonsTextures();
    int activeButtonIndex = 0;
private:
    SDL_Texture* buttonTexture;
    SDL_Texture* clickedButtonTexture;
};


#endif //BULLET_HELL_5_MENU_H
