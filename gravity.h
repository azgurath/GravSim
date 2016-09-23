#ifndef GRAVITY_H
#define GRAVITY_H

#include "particle.h"

class Gravity
{
public:
    Gravity(int preset);
    ~Gravity();

    void remove(Particle *part);
    void removeList();
    void update();
    void add(Particle *part);
    int partNum();
    float color(int pos);
    float x(int pos);
    float y(int pos);
    float z(int pos);
    void collide(Particle *part1, Particle *part2);

private:
    Particle *particle;
    float maxMass;
    int particleCount;
};

#endif // GRAVITY_H
