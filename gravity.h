#ifndef GRAVITY_H
#define GRAVITY_H

#include "particle.h"

const int NUM_P = 2;

class Gravity
{
public:
    Gravity();

    void remove();
    void update();
    float x(int pos);
    float y(int pos);
    float z(int pos);

private:
    Particle *particle[NUM_P];
};

#endif // GRAVITY_H
