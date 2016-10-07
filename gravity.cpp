/**
  * @file gravity.cpp
  * @author Andrew Hoover
  * @date 9/29/2016
  * @brief Implmentation of Gravity class.
  *
  * Implementation of Gravity class. Includes functions
  * to manage linked list of particles, move particles
  * based on gravity, and create and destroy the environment.
  */
#include <math.h>
#include <QDebug>
#include "gravity.h"

extern bool REMOVE;
extern float GRAVITY_FORCE;

/**
 * Constructor.
 *
 * @brief Gravity::Gravity
 * @param preset number to use to create particles
 */
Gravity::Gravity(int preset){
    particle = new(Particle);

    // Create a series of particles based on the preset value chosen.
    // Add them to the linked list.
    if(preset == 2)
    {
        particle->mass = 100;
        particleCount = 1;

        Particle *tmpPart = new(Particle);
        tmpPart->x = 10;
        tmpPart->y = 10;
        tmpPart->z = 30;
        tmpPart->angX = 0.05;
        tmpPart->angY = 0.05;
        tmpPart->angZ = -0.03;
        tmpPart->mass = 1;
        add(tmpPart);

        tmpPart = new(Particle);
        tmpPart->x = 100;
        tmpPart->y = 0;
        tmpPart->z = 0;
        tmpPart->angX = 0.0;
        tmpPart->angY = -0.03;
        tmpPart->angZ = 0.0;
        tmpPart->mass = 10;
        tmpPart->next = 0;
        add(tmpPart);

        tmpPart = new(Particle);
        tmpPart->x = 80;
        tmpPart->y = 10;
        tmpPart->z = 0;
        tmpPart->angX = 0.03;
        tmpPart->angY = -0.015;
        tmpPart->angZ = 0.0;
        tmpPart->mass = 1;
        tmpPart->next = 0;
        add(tmpPart);

        maxMass = 100;
    }
    if(preset == 1)
    {
        particle->mass = 100;
        particleCount = 1;

        Particle *tmpPart = new(Particle);
        tmpPart->x = 20;
        tmpPart->y = 20;
        tmpPart->z = 0;
        tmpPart->angX = 0.05;
        tmpPart->angY = 0.05;
        tmpPart->angZ = 0.0;
        add(tmpPart);

        tmpPart = new(Particle);
        tmpPart->x = -50;
        tmpPart->y = 0;
        tmpPart->z = 0;
        tmpPart->angX = 0.0;
        tmpPart->angY = 0.05;
        tmpPart->angZ = 0.0;
        tmpPart->mass = 100;
        tmpPart->next = 0;
        add(tmpPart);

        maxMass = 100;
    }
}

/**
 * Length of linked list
 *
 * @brief Gravity::partNum
 * @return length of linked list
 */

int Gravity::partNum(){
    return particleCount;
}

/**
 * Add new particle to linked list.
 *
 * @brief Gravity::add
 * @param part Pointer to new particle to add.
 */

void Gravity::add(Particle *part){
    Particle *tmp = particle;
    while(tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = part;
    part->next = NULL;
    particleCount++;
}

/**
 * Delete given particle from linked list.
 *
 * @brief Gravity::remove
 * @param part Pointer to particle to remove.
 */

void Gravity::remove(Particle *part){
    Particle *prev = NULL;
    Particle *curr = particle;
    Particle *tmp = NULL;
    while(curr != NULL)
    {
        if(curr == part)
        {
            // delete from front of list
            if(prev == NULL)
            {
                tmp = particle->next;
                delete particle;
                particle = part;
                part->next = tmp;
            }
            // delete from middle or end of list
            else
            {
                tmp = curr->next;
                delete curr;
                prev->next = tmp;
            }
        }
        prev = curr;
        curr = curr->next;
    }
    particleCount--;
}

/**
 * Delete every node in linked list. Use to avoid memory leaks.
 *
 * @brief Gravity::removeList
 */

void Gravity::removeList(){
    particleCount = 0;
    Particle *tmp = particle;
    Particle *next = particle;
    while(tmp != NULL)
    {
        next = tmp->next;
        delete tmp;
        tmp = next;
    }
}

/**
 * Move particles based on velocity and gravity.
 *
 * @brief Gravity::update
 */

void Gravity::update(){
    float acceleration, speed;
    float diffX, diffY, diffZ, length; // velocity vector.
    float distance;
    // Walk through all particles
    Particle *tmpPart1 = particle;
    Particle *tmpPart2 = particle;
    while(tmpPart1 != 0)
    {
        tmpPart2 = particle;
        // For each particle, walk through each other particle
        while(tmpPart2 !=0)
        {
            // Don't have the particle move due to it's own gravity
            if(tmpPart1 != tmpPart2)
            {
                // Solve for acceleration due to gravity
                distance = pow(tmpPart1->x - tmpPart2->x, 2);
                distance += pow(tmpPart1->y - tmpPart2->y, 2);
                distance += pow(tmpPart1->z - tmpPart2->z, 2);
                distance = sqrt(distance);
                acceleration = GRAVITY_FORCE * (tmpPart1->mass)/(distance*distance);
                speed = acceleration / 60.0; // multiple by time for speed.
                // Compute velocity vector
                diffX = tmpPart1->x - tmpPart2->x;
                diffY = tmpPart1->y - tmpPart2->y;
                diffZ = tmpPart1->z - tmpPart2->z;
                length = sqrt((diffX*diffX) + (diffY*diffY) + (diffZ*diffZ));

                // They collided, remove particle with less mass
                if(distance < 1)
                {
                    // Find particle with less mass
                    if(tmpPart1->mass < tmpPart2->mass)
                    {
                        collide(tmpPart1, tmpPart2);
                        // Delete the particle
                        Particle *tmp = tmpPart1->next;
                        remove(tmpPart1);
                        tmpPart1 = tmp;
                    }
                    else
                    {
                        collide(tmpPart2, tmpPart1);
                        // Delete the particle
                        Particle *tmp = tmpPart2->next;
                        remove(tmpPart2);
                        tmpPart2 = tmp;
                    }
                }
                // They didn't collide, update velocity vector
                else
                {
                    diffX /= length;
                    diffY /= length;
                    diffZ /= length;
                    diffX *= speed;
                    diffY *= speed;
                    diffZ *= speed;
                    // Add speed vector from gravity to current velocity vector.
                    tmpPart2->angX += diffX;
                    tmpPart2->angY += diffY;
                    tmpPart2->angZ += diffZ;
                }
            }
            // move to next particle
            // Might be null if we deleted last particle in a collision
            if(tmpPart2 != NULL)
                tmpPart2 = tmpPart2->next;
        }
        // Move the particle according to it's final velocity vector,
        //     after being updated by the gravity of all other particles.
        tmpPart1->x += tmpPart1->angX;
        tmpPart1->y += tmpPart1->angY;
        tmpPart1->z += tmpPart1->angZ;
        // move to next particle
        // qDebug() << tmpPart1 << tmpPart1->next;
        tmpPart1 = tmpPart1->next;
    }
}


/**
 * Collide two particles, the smaller is deleted and the larger
 * updated in mass and velocity based on the collision.
 *
 * @brief Gravity::collide
 * @param part1 Lighter particle in collision.
 * @param part2 Heavier particle in collision.
 */
void Gravity::collide(Particle *part1, Particle *part2){
    // Compute how much it's velocity changes
    float newX = part1->mass * part1->angX;
    float newY = part1->mass * part1->angY;
    float newZ = part1->mass * part1->angZ;
    newX += part2->mass * part2->angX;
    newY += part2->mass * part2->angY;
    newZ += part2->mass * part2->angZ;
    newX /= part1->mass + part2->mass;
    newY /= part1->mass + part2->mass;
    newZ /= part1->mass + part2->mass;
    part2->angX = newX;
    part2->angY = newY;
    part2->angZ = newZ;
    // Add it's mass to the other particle
    part2->mass += part1->mass;
}

/**
 * X location of particle at location pos in the linked list.
 *
 * @brief Gravity::x
 * @param pos Position in the linked list.
 * @return
 */

float Gravity::x(int pos){
    Particle *part = particle;
    for(int i = 0; i < pos; i++)
        part = part->next;
    return part->x;
}

/**
 * Y location of particle at location pos in the linked list.
 *
 * @brief Gravity::y
 * @param pos Position in the linked list.
 * @return
 */

float Gravity::y(int pos){
    Particle *part = particle;
    for(int i = 0; i < pos; i++)
        part = part->next;
    return part->y;
}

/**
 * Z location of particle at location pos in the linked list.
 *
 * @brief Gravity::z
 * @param pos Position in the linked list.
 * @return
 */

float Gravity::z(int pos){
    Particle *part = particle;
    for(int i = 0; i < pos; i++)
        part = part->next;
    return part->z;
}

/**
 * Color to draw the particle at location pos in the linked list.
 *
 * @brief Gravity::color
 * @param pos Position in the linked list.
 * @return color to draw particle.
 */

float Gravity::color(int pos){
    // Return the percentage of mass compared to the heaviest particle
    // to determine which color to draw the particle as.
    Particle *part = particle;
    for(int i = 0; i < pos; i++)
        part = part->next;
    return part->mass / maxMass;
}

/**
 * Deconstructor, cleans up the linked list without leaking memory.
 *
 * @brief Gravity::~Gravity
 */

Gravity::~Gravity(){
    removeList();
}
