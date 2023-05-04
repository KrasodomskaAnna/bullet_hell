#ifndef BULLET_HELL_5_RANDOM_H
#define BULLET_HELL_5_RANDOM_H
#pragma once
#include "./SDL2-2.0.10/include/SDL.h"
#include "./SDL2-2.0.10/include/SDL_main.h"
#include <cstdlib>
#include <ctime>


float random(float min, float max);

float randomMin(float min);

float randomMax(float max);

bool randomChoice();


#endif //BULLET_HELL_5_RANDOM_H
