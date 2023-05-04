#ifndef BULLET_HELL_2_GAME_WINDOW_H
#define BULLET_HELL_2_GAME_WINDOW_H
#pragma once
#include <cstdio>
#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include "math_vector.h"

class GameWindow {
public:
    GameWindow(const char* title, int width, int height);

    // funckja wyswietla odpowiednie elementy w zadanym miejscu z zadana tekstura
    void render(int x, int y, SDL_Texture* texture);
    // .._.. pod zadanym katem
    void render(int x, int y, SDL_Texture* texture, float angle);
    // .._.. z zeskalowaną wielkoscia, gdzie przekazywana jest skala w osi OX i OY
    void render(int x, int y, SDL_Texture *texture, float scaleX, float scaleY);
    void render(int x, int y, SDL_Texture *texture, int width, int height, float scaleX, float scaleY);
    // funkcja wyrysowuje tekst z zeskalowana wielkoscia
    void drawText(int x, int y, const char *text, SDL_Texture* texture, float scale);
    // niszczy render i window
    void cleanUp();
    // wyswietla render
    void display();
    // czysci render
    void clear();

    // funkcja zwraca renderer
    SDL_Renderer* getRenderer();
    // funkcja zwraca window
    SDL_Window* getWindow();
    math_vector getPos(){
        return position;
    }
    void setPos(float x, float y){
        position = math_vector{x, y};
    }
    void setBgDimensions(SDL_Texture* backgroundTexture);
    void setBgDimensions(int width, int height);
    // funkcje zwracaja odpowiednie wymiary okna
    int getBoardW();
    int getBoardH();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    // zmienne przechowuja wymiary okna
    int boardW = 0;
    int boardH = 0;
    math_vector position{0.0,0.0};
};



#endif //BULLET_HELL_2_GAME_WINDOW_H
