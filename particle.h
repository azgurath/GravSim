/**
  * @file particle.h
  * @author Andrew Hoover
  * @date 9/20/2016
  * @brief Particle class for linked list.
  *
  * Particle class decleration for node in linked list. Hold the location,
  * velocity, mass and next node in the list for each particle.
  */

#ifndef PARTICLE_H
#define PARTICLE_H

/**
 * Holds the location, velocity, mass and next node in the linked list
 * for a given particle. The constructor initializes all values to zero.
 *
 * @brief The Particle class
 */

class Particle
{
public:
    Particle();

    float x, y, z; // position
    float angX, angY, angZ; // velocity vector
    float mass; // mass

    Particle *next; // next node
};

#endif // PARTICLE_H
