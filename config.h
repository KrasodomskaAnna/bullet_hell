#ifndef BULLET_HELL_5_CONFIG_H
#define BULLET_HELL_5_CONFIG_H
#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "vector.h"
#include "block.h"
#include "enemy.h"
#include "const.h"



class Config {
public:
    Config(const char* path, int level, int* advancedAttackFrequency, Vector<Block*>* blocks, Vector<Enemy*>* enemies, GameWindow *gameWindow, SDL_Texture *enemyTexture, SDL_Texture *animationEnemyTexture, List<Bullet*>* bullets, SDL_Texture *bulletsTexture, SDL_Texture *blocksTexture) {
        this->rawFile = fopen(path, "r"); // otwieranie pliku
        this->targetLevel = level;
        this->advancedAttackFrequency = advancedAttackFrequency;
        this->blocks = blocks;
        this->blocksTexture = blocksTexture;
        this->bulletsTexture = bulletsTexture;
        this->enemies = enemies;
        this->gameWindow = gameWindow;
        this->enemyTexture = enemyTexture;
        this->animationEnemyTexture = animationEnemyTexture;
        this->bullets = bullets;
        this->bulletsTexture = bulletsTexture;

    }

    void load() {
        this->currentLevel = 0; // przechowuje level aktualnie wczytywany przez config
        char optionType[6]; // najdluzszym typem opcji jest "Enemy", dlatego optionType przechowuje do 6 char (5 od "Enemy" + 0 jako null)
        int i; // do iteracji wsrodku switch cases

        while(!feof(this->rawFile)) { // powtarzaj dopoki nie dojdziesz do konca EOF
            char line[CONFIG_MAX_LINE_LENGTH]; // Buffer do przechowywania lini
            fgets(line, CONFIG_MAX_LINE_LENGTH, this->rawFile); // wczytuje linie
            auto len = strlen(line); // zbiera dlugosc lini

            auto indent = 0;
            while (indent < len && line[indent] == ' ') { // liczy indent -> ilosc spacji
                indent++;
            }
            switch (indent) {
                case 0: // Aby inne opcje mogly byc latwododawalne w przyszlosci
                    this->checkForLoadingCustom();
                    char buffer[6];
                    if (strncmp(strncpy(buffer, line, 6), "levels", 6) != 0)
                        Config::displayError("Unsupported config option");
                    break;
                case 4:
                    this->checkForLoadingCustom();
                    this->currentLevel = 0; // reset aktualnego level
                    i = 0; // zmienna do iteracji po liniach
                    while (i + 4 < len) { // zatrzymuje sie gdy dochodzi do konca "lini" --- + 4 bo case 4, jestesmy w 4-tym wcieciu
                        if (line[i + 4] == ':') break; // znak ':' oznacza koniec lini
                        if (line[i + 4] > 47 && line[i] < 58) { // jezeli char jest w zakresie od 48 (ASCII dla 0) do 57 (ASCII dla 9) jest numerem
                            this->currentLevel *= 10; // przesuwa program do innej cyfry z numerze
                            this->currentLevel += (line[i + 4] - 48); // 48 jest ASCII dla 0, wiec jest odejmowane aby przekonwertowac z char do int
                        } else
                            Config::displayError("Invalid number");
                        i++; // idz do nastepnego znaku
                    }
                    break;
                case 8:
                    this->checkForLoadingCustom();
                    sscanf(line, "%5s", optionType); // wyciagnij optionType z lini
                    optionType[5] = 0; // "null termination"
                    if (strncmp(optionType, "Enemy", 5) == 0) {
                        if (this->loadEnemy(line, len)) {
                            this->loadingCustomShootingPattern = true;
                            this->customShootingPatternBullets.clear();
                        }
                    } else if (strncmp(optionType, "Block", 5) == 0)
                        this->loadBlock(line, len);
                    else if (strncmp(optionType, "AFreq", 5) == 0)
                        this->loadAdvancedAttackFrequency(line, len);
                    else if (strncmp(optionType, "BSize", 5) == 0)
                        this->loadBoardSize(line, len);
                    else
                        Config::displayError("Unexpected token");
                    break;
                case 12:
                    if (!this->loadingCustomShootingPattern) // brak enemy do wczytania
                        Config::displayError("Unexpected indent");
                    this->loadBullet(line, len);
                    break;
                default:
                    Config::displayError("Invalid indentation");
            }
        }
        if (this->loadingCustomShootingPattern) // jezeli ostatnia linia bylo EOF przestan ladowac custom shooting pattern
            this->checkForLoadingCustom();
    }

    ~Config() {
        fclose(this->rawFile); // zamknij plik
    }

private:
    FILE* rawFile;
    int currentLevel = 0;
    bool loadingCustomShootingPattern = false;
    Vector<BulletConfig> customShootingPatternBullets;
    char* customEnemyLine{};
    int targetLevel;
    unsigned int customEnemyLineLen{};
    int* advancedAttackFrequency;
    Vector<Block*>* blocks;
    SDL_Texture *blocksTexture;
    Vector<Enemy*>* enemies;
    GameWindow *gameWindow;
    SDL_Texture *enemyTexture;
    SDL_Texture *animationEnemyTexture;
    List<Bullet*>* bullets;
    SDL_Texture *bulletsTexture;

    static void displayError(const char* msg) { // pozwala wyswietlac  error'y
        printf("Failed to parse the config file: %s\n", msg);
        exit(1); // konczy program gdy error
    }

    void loadAdvancedAttackFrequency(char* line, unsigned int len) {
        if(this->currentLevel == this->targetLevel) {
            char optionType[6];
            sscanf(line, "%s %d", optionType, this->advancedAttackFrequency);
        }
    }

    void loadBoardSize(char* line, unsigned int len) {
        if(this->currentLevel == this->targetLevel) {
            char optionType[6];
            int width, height;
            sscanf(line, "%s %d %d", optionType, &width, &height);
            this->gameWindow->setBgDimensions(width, height);
        }
    }

    bool loadEnemy(char* line, unsigned int len) { // zwraca true jezeli custom shooting pattern musi byc zaladowany
        int x, y;
        // optionType jest Enemy + "null termination"
        char optionType[6], texturePath[CONFIG_MAX_LINE_LENGTH], animationTexturePath[CONFIG_MAX_LINE_LENGTH]; // path nie moze byc dluzszy niz maxymalna dlugosc lini
        char shootingPatternType[7]; // 7 poniewaz "custom" + "null termination"
        sscanf(line, "%5s %d %d %s %s %7s", optionType, &x, &y, texturePath, animationTexturePath, shootingPatternType);

        // "null termination"
        optionType[5] = 0;
        shootingPatternType[6] = 0;

        if(strncmp(shootingPatternType, "custom", 6) == 0 && !this->loadingCustomShootingPattern) {
            this->customEnemyLine = new char[len](); // przydziela pamiec
            this->customEnemyLineLen = len;
            strncpy(this->customEnemyLine, line, len); // tworzy kopie zapasowa lini, w celu pozniejszego uzycia
            return true;
        } else if (this->loadingCustomShootingPattern) {
            for (int i = 0; i < this->customShootingPatternBullets.size(); i++) {
                if(this->targetLevel == this->currentLevel) {
                    Vector<BulletConfig>* bulletsCopy = new Vector<BulletConfig>();
                    for (int i = 0; i < this->customShootingPatternBullets.size(); i++) {
                        bulletsCopy->push_back(this->customShootingPatternBullets[i]);
                    }
                    this->enemies->push_back(new Enemy(this->gameWindow, x, y, this->enemyTexture, this->animationEnemyTexture, this->bullets, this->bulletsTexture, EnemyType::custom, bulletsCopy));
                }
            }
            return false;
        }
        if(this->targetLevel == this->currentLevel) {
            EnemyType type = EnemyType::any;
            if (strncmp(shootingPatternType, "even", 4) == 0)
                type = EnemyType::even;
            else if (strncmp(shootingPatternType, "accent", 6) == 0)
                type = EnemyType::accent;
            else if (strncmp(shootingPatternType, "killer", 6) == 0)
                type = EnemyType::killer;
            else if (strncmp(shootingPatternType, "rand", 4) == 0)
                type = EnemyType::rand;
            else if (strncmp(shootingPatternType, "any", 3) == 0)
                type = EnemyType::any;
            else
                Config::displayError("Invalid shooting pattern type");
            this->enemies->push_back(new Enemy(this->gameWindow, x, y, this->enemyTexture, this->animationEnemyTexture, this->bullets, this->bulletsTexture, type));
        }

        return false;
    }

    void loadBlock(char* line, unsigned int len) {
        int x, y;
        // optionType jest Enemy + "null termination"
        char optionType[6], texturePath[CONFIG_MAX_LINE_LENGTH], animationTexturePath[CONFIG_MAX_LINE_LENGTH]; // path nie moze byc dluzszy niz maxymalna dlugosc lini
        sscanf(line, "%5s %d %d %s %s", optionType, &x, &y, texturePath, animationTexturePath);

        // "null termination"
        optionType[5] = 0;

        this->blocks->push_back(new Block(x, y, this->blocksTexture));
    }

    void loadBullet(char* line, unsigned int len) {
        BulletConfig bullet;
        char optionType[7]; // "Bullet" + null termination
        sscanf(line, "%6s %d %f", optionType, &bullet.angle, &bullet.speed);

        // "null termination"
        optionType[6] = 0;

        if (strncmp(optionType, "Bullet", 6) != 0)
            Config::displayError("Unexpected token");

        this->customShootingPatternBullets.push_back(bullet);
    }

    void checkForLoadingCustom() { // powinno byc wywolywane dla kazdego przypadku poza bullet'ami
        if (this->loadingCustomShootingPattern) {
            if (this->customShootingPatternBullets.size() == 0)
                Config::displayError("Missing bullets for a custom shooting config");

            this->loadEnemy(this->customEnemyLine, this->customEnemyLineLen);
            delete[] this->customEnemyLine; // zwalnia pamiec
            this->customEnemyLineLen = 0;

            this->loadingCustomShootingPattern = false; // przestan wczytywac custom shooting pattern
        };
    }
};
#endif //BULLET_HELL_5_CONFIG_H

