#ifndef BULLET_HELL_5_COLLISION_H
#define BULLET_HELL_5_COLLISION_H

// funkcja sprawdza kolizje dla dwoch prostokatow
// zwraca true gdy koliduja ze soba, w przeciwny wypadku zwraca false
bool willCollideBox(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);

#endif //BULLET_HELL_5_COLLISION_H
