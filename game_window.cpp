#include "game_window.h"

GameWindow::GameWindow(const char *title, int width, int height) {
    // tworzenie okna gry
    this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    // jezeli operacja się nie udala, wypisuje iz nastapil blad
    if(this->window == nullptr)
        printf("Nie udało się stworzyć window. ERROR: %s \n", SDL_GetError());

    // tworzenie renderera (to co jest w okienku gry), ktory przyjmuje render do window i uwzglednia pierwsza flage
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
}

void GameWindow::render(int x, int y, SDL_Texture *texture) {
    // tworzenie prostokata x, y w SDL o zadanej teksturze
    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    source.w;
    source.h;
    SDL_QueryTexture(texture, nullptr, nullptr, &source.w, &source.h);
    SDL_Rect destination;
    destination.x = x;
    destination.y = y;
    destination.w = source.w;
    destination.h = source.h;
    // przekazanie tekstury i recta do renderera
    SDL_RenderCopy(this->renderer, texture, &source, &destination);
}

void GameWindow::display() {
    SDL_RenderPresent(this->renderer);
}

void GameWindow::clear() {
    SDL_RenderClear(this->renderer);
}

void GameWindow::cleanUp() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}

SDL_Renderer *GameWindow::getRenderer() {
    return this->renderer;
}

SDL_Window *GameWindow::getWindow() {
    return this->window;
}

int GameWindow::getBoardW() {
    return boardW;
}

int GameWindow::getBoardH() {
    return boardH;
}

void GameWindow::setBgDimensions(SDL_Texture* backgroundTexture) {
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &this->boardW, &this->boardH);
}

void GameWindow::setBgDimensions(int width, int height) {
    this->boardW = width;
    this->boardH = height;
}

void GameWindow::render(int x, int y, SDL_Texture *texture, float angle) {
    // tworzenie prostokata x, y w SDL o zadanej teksturze
    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    source.w;
    source.h;
    SDL_QueryTexture(texture, nullptr, nullptr, &source.w, &source.h);
    SDL_Rect destination;
    destination.x = x;
    destination.y = y;
    destination.w = source.w;
    destination.h = source.h;
    // przekazanie tekstury (obroconej pod zadanym katem) i recta do renderera
    SDL_RenderCopyEx(this->renderer, texture, &source, &destination, angle, nullptr, SDL_FLIP_NONE);
}

void GameWindow::render(int x, int y, SDL_Texture *texture, float scaleX, float scaleY) {
    // tworzenie prostokata x, y w SDL o zadanej teksturze
    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    source.w;
    source.h;
    SDL_QueryTexture(texture, nullptr, nullptr, &source.w, &source.h);
    SDL_Rect destination;
    destination.x = x;
    destination.y = y;
    // zeskalowanie  tekstury poprzez zadane skale w osiach OX i OY
    destination.w = source.w * scaleX;
    destination.h = source.h * scaleY;
    // przekazanie tekstury i recta do renderera
    SDL_RenderCopy(this->renderer, texture, &source, &destination);
}

void GameWindow::render(int x, int y, SDL_Texture *texture, int width, int height, float scaleX, float scaleY) {
    // tworzenie prostokata x, y w SDL o zadanej teksturze
    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    source.w;
    source.h;
    SDL_QueryTexture(texture, nullptr, nullptr, &source.w, &source.h);
    SDL_Rect destination;
    destination.x = x;
    destination.y = y;
    // zeskalowanie  tekstury poprzez zadane skale w osiach OX i OY
    destination.w = width * scaleX;
    destination.h = height * scaleY;
    // przekazanie tekstury i recta do renderera
    SDL_RenderCopy(this->renderer, texture, &source, &destination);
}

void GameWindow::drawText(int x, int y, const char *text, SDL_Texture *texture, float scale) {
    int px, py, c;
    SDL_Rect s, d;
    s.w = 8;
    s.h = 8;
    d.w = 8 * scale;
    d.h = 8 * scale;
    while (*text)
    {
        c = *text & 255;
        px = (c % 16) * 8;
        py = (c / 16) * 8;
        s.x = px;
        s.y = py;
        d.x = x;
        d.y = y;
        SDL_RenderCopy(this->renderer, texture, &s, &d);
        x += 8 * scale;
        text++;
    };
}
