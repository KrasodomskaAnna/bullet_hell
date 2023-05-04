#ifndef BULLET_HELL_2_MATH_VECTOR_H
#define BULLET_HELL_2_MATH_VECTOR_H

// typ analogiczny do zapisu punktu na plaszczyznie w matematyce
struct math_vector {
    float x;
    float y;
    math_vector(float positionX, float positionY): x(positionX), y(positionY){}
};


#endif //BULLET_HELL_2_MATH_VECTOR_H
