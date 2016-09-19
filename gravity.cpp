#include <math.h>
#include <QDebug>
#include "gravity.h"

Gravity::Gravity(){
    for(int i = 0; i < NUM_P; i++)
    {
        particle[i] = new(Particle);
    }
    particle[0]->mass = 100;

    particle[1]->x = 20;
    particle[1]->y = 20;
    particle[1]->z = 0;
    particle[1]->angX = 0.05;
    particle[1]->angY = 0.05;
    particle[1]->angZ = 0.0;

    particle[2]->x = -50;
    particle[2]->y = 0;
    particle[2]->z = 0;
    particle[2]->angX = 0.0;
    particle[2]->angY = 0.05;
    particle[2]->angZ = 0.0;
    particle[2]->mass = 100;

    maxMass = 100;
}

void Gravity::remove(){
    for(int i = 0; i < NUM_P; i++)
    {
        delete(particle[i]);
    }
}

void Gravity::update(){
    float acceleration, speed;
    float diffX, diffY, diffZ, length; // velocity vector. God help us.
    float distance;
    // Walk through all particles
    for(int i = 0; i < NUM_P; i++)
    {
        // For each particle, walk through each other particle
        for(int j = 0; j < NUM_P; j++)
        {
            // Don't have the particle move due to it's own gravity
            if(i != j)
            {
                // Solve for acceleration due to gravity
                distance = pow(particle[i]->x - particle[j]->x, 2);
                distance += pow(particle[i]->y - particle[j]->y, 2);
                distance += pow(particle[i]->z - particle[j]->z, 2);
                distance = sqrt(distance);
                acceleration = 0.1 * (particle[i]->mass)/(distance*distance);
                speed = acceleration / 60.0; // multiple by time for speed.
                // Compute speed vector
                diffX = particle[i]->x - particle[j]->x;
                diffY = particle[i]->y - particle[j]->y;
                diffZ = particle[i]->z - particle[j]->z;
                length = sqrt((diffX*diffX) + (diffY*diffY) + (diffZ*diffZ));

                // They collided, make them in the same place and velocity
                if(length < 1)
                {
                    particle[j]->x = particle[i]->x;
                    particle[j]->y = particle[i]->y;
                    particle[j]->z = particle[i]->z;
                    particle[j]->angX = particle[i]->angX;
                    particle[j]->angY = particle[i]->angY;
                    particle[j]->angZ = particle[i]->angZ;
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
                    particle[j]->angX += diffX;
                    particle[j]->angY += diffY;
                    particle[j]->angZ += diffZ;
                }
            }
        }
        // Move the particle according to it's final velocity vector,
        //     after being updated by the gravity of all other particles.
        particle[i]->x += particle[i]->angX;
        particle[i]->y += particle[i]->angY;
        particle[i]->z += particle[i]->angZ;
    }
}

float Gravity::x(int pos){
    return particle[pos]->x;
}

float Gravity::y(int pos){
    return particle[pos]->y;
}

float Gravity::z(int pos){
    return particle[pos]->z;
}

float Gravity::color(int pos){
    return particle[pos]->mass / maxMass;
}
