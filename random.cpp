#include "random.h"

float random(float min, float max) {
    srand (static_cast <unsigned> (SDL_GetTicks()));
    return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
}

float randomMin(float min) {
    srand (static_cast <unsigned> (SDL_GetTicks()));
    return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX));
}

float randomMax(float max) {
    srand (static_cast <unsigned> (SDL_GetTicks()));
    return static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/max));
}

bool randomChoice() {
    return round(randomMax(1));
}
