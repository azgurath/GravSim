#ifndef GRAVITY_H
#define GRAVITY_H

#include "particle.h"

const int NUM_P = 3;

class Gravity
{
public:
    Gravity();

    void remove();
    void update();
    float color(int pos);
    float x(int pos);
    float y(int pos);
    float z(int pos);

private:
    Particle *particle[NUM_P];
    float maxMass;
};

#endif // GRAVITY_H
