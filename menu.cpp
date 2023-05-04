#include "menu.h"

Menu::Menu(SDL_Texture* buttonTexture, SDL_Texture* clickedButtonTexture) {
    this->buttonTexture = buttonTexture;
    this->clickedButtonTexture = clickedButtonTexture;
    float offset = 260;
    buttons.push_back(new Button("level 0", this->clickedButtonTexture, {BUTTON_POSITION_X, offset}));
    offset += DELTA_BUTTONS_POSITION_Y;
    buttons.push_back(new Button("level 1", this->buttonTexture, {BUTTON_POSITION_X, offset}));
    offset += DELTA_BUTTONS_POSITION_Y;
    buttons.push_back(new Button("level 2", this->buttonTexture, {BUTTON_POSITION_X, offset}));
    offset += DELTA_BUTTONS_POSITION_Y;
    buttons.push_back(new Button("level 3", this->buttonTexture, {BUTTON_POSITION_X, offset}));
    offset += DELTA_BUTTONS_POSITION_Y;
    buttons.push_back(new Button("level 4", this->buttonTexture, {BUTTON_POSITION_X, offset}));
    offset += DELTA_BUTTONS_POSITION_Y;
    buttons.push_back(new Button("score board", this->buttonTexture, {BUTTON_POSITION_X, offset}));
    offset += DELTA_BUTTONS_POSITION_Y;
    buttons.push_back(new Button("quit game", this->buttonTexture, { BUTTON_POSITION_X, offset }));
}

void Menu::updateButtonsTextures() {
    for(int i = 0; i < buttons.size(); i++) {
        buttons[i]->texture = i == activeButtonIndex ? clickedButtonTexture : buttonTexture;
    }
}


