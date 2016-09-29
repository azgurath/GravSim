#ifndef GRAVITY_H
#define GRAVITY_H

#include "particle.h"

class Gravity
{
public:
    Gravity(int preset); // generate universe to given preset specifications
    ~Gravity(); // no memory leaks

    void remove(Particle *part); // remove particle from list
    void removeList(); // delete entire list, returning memory to OS
    void update(); // move particles
    void add(Particle *part); // add particle to list
    int partNum(); // length of linked list
    float color(int pos); // color to draw the particle at given position in list
    float x(int pos); // location of particle at given position in list
    float y(int pos);
    float z(int pos);
    void collide(Particle *part1, Particle *part2); // make two particles collide

private:
    Particle *particle; // first node in linked list
    float maxMass; // most heavy particle, used for color
    int particleCount; // lenght of linked list
};

#endif // GRAVITY_H
