#include "gravity.h"

Gravity::Gravity(){
    for(int i = 0; i < NUM_P; i++)
    {
        particle[i] = new(Particle);
    }
    particle[0]->mass = 100;

    particle[1]->angX = 0.7;
    particle[1]->angY = 0.5;
    particle[1]->angZ = 0.3;
    particle[1]->speed = 0.01;
}

void Gravity::remove(){
    for(int i = 0; i < NUM_P; i++)
    {
        delete(particle[i]);
    }
}

void Gravity::update(){
    for(int i = 0; i < NUM_P; i++)
    {
        particle[i]->x += particle[i]->speed * particle[i]->angX;
        particle[i]->y += particle[i]->speed * particle[i]->angY;
        particle[i]->z += particle[i]->speed * particle[i]->angZ;
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
