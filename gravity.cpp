#include <math.h>
#include <QDebug>
#include "gravity.h"

Gravity::Gravity(){
    particle = new(Particle);

    particle->mass = 100;
    particleCount = 1;

    Particle *tmpPart = new(Particle);
    tmpPart->x = 10;
    tmpPart->y = 10;
    tmpPart->z = 30;
    tmpPart->angX = 0.05;
    tmpPart->angY = 0.05;
    tmpPart->angZ = -0.03;
    add(tmpPart);

    tmpPart = new(Particle);
    tmpPart->x = 100;
    tmpPart->y = 0;
    tmpPart->z = 0;
    tmpPart->angX = 0.0;
    tmpPart->angY = -0.03;
    tmpPart->angZ = 0.0;
    tmpPart->mass = 100;
    tmpPart->next = 0;
    add(tmpPart);

    maxMass = 100;
}

int Gravity::partNum(){
    return particleCount;
}

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

void Gravity::update(){
    float acceleration, speed;
    float diffX, diffY, diffZ, length; // velocity vector. God help us.
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
                acceleration = 0.2 * (tmpPart1->mass)/(distance*distance);
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
            tmpPart2 = tmpPart2->next;
        }
        // Move the particle according to it's final velocity vector,
        //     after being updated by the gravity of all other particles.
        tmpPart1->x += tmpPart1->angX;
        tmpPart1->y += tmpPart1->angY;
        tmpPart1->z += tmpPart1->angZ;
        // move to next particle
        tmpPart1 = tmpPart1->next;
    }
}

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

float Gravity::x(int pos){
    Particle *part = particle;
    for(int i = 0; i < pos; i++)
        part = part->next;
    return part->x;
}

float Gravity::y(int pos){
    Particle *part = particle;
    for(int i = 0; i < pos; i++)
        part = part->next;
    return part->y;
}

float Gravity::z(int pos){
    Particle *part = particle;
    for(int i = 0; i < pos; i++)
        part = part->next;
    return part->z;
}

float Gravity::color(int pos){
    Particle *part = particle;
    for(int i = 0; i < pos; i++)
        part = part->next;
    return part->mass / maxMass;
}
