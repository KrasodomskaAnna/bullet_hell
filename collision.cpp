#include "collision.h"

bool willCollideBox(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
    bool left = (x1 >= x2 && x1 < x2 + w2);
    bool right = (x1 + w1 > x2 && x1 + w1 <= x2 + w2);
    bool edgeX = ((x1 < x2 && x1 + w1 > x2 + w2) || left || right);
    bool top = (y1 >= y2 && y1 < y2 + h2);
    bool bottom = (y1 + h1 > y2 && y1 + h1 <= y2 + h2);
    bool edgeY = ((y1 < y2 && y1 + h1 > y2 + h2) || top || bottom);

    return edgeX && edgeY;
}

