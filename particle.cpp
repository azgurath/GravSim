/**
  * @file particle.cpp
  * @author Andrew Hoover
  * @date 9/20/2016
  * @brief Implementation of particle class.
  *
  * Implements the constructor for the particle class,
  * initializing the location, velocity, mass and next
  * particle to zero.
  */

#include "particle.h"

/**
 * Constructor, initializes the particle to zero.
 *
 * @brief Particle::Particle
 */

Particle::Particle()
{
    // Set every variable to zero but mass, which is set to 1.
    x = 0.0;
    y = 0.0;
    z = 0.0;
    angX = 0.0;
    angY = 0.0;
    angZ = 0.0;
    mass = 1.0;

    next = 0;
}

