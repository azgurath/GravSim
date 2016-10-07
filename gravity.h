/**
  * @file gravity.h
  * @author Andrew Hoover
  * @date 9/29/2016
  * @brief Gravity class, holds the linked list of particles and methods to
  * update the universe.
  *
  * The Gravity class holds a pointer to the first node in the linked list of
  * particles, and has methods to manipulate the list in the forms of adding
  * and removing particles, and the entire list. Also has methods for updating
  * the locations and velocities of the particles by calculating the force
  * of gravity they exert on each other.
  */

#ifndef GRAVITY_H
#define GRAVITY_H

#include "particle.h"

/**
  * Holds a pointer to the first node in the linked list of
  * particles, and has methods to manipulate the list in the forms of adding
  * and removing particles, and the entire list. Also has methods for updating
  * the locations and velocities of the particles by calculating the force
  * of gravity they exert on each other.
  *
  * @brief The Gravity class
  */

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
