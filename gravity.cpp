#include <math.h>
#include <QDebug>
#include "gravity.h"

Gravity::Gravity(){
    for(int i = 0; i < NUM_P; i++)
    {
        particle[i] = new(Particle);
    }
    particle[0]->mass = 100;

    particle[1]->angX = 0.007;
    particle[1]->angY = 0.005;
    particle[1]->angZ = 0.003;
    particle[1]->speed = 0.01;
}

void Gravity::remove(){
    for(int i = 0; i < NUM_P; i++)
    {
        delete(particle[i]);
    }
}

void Gravity::update(){
    float acceleration;
    float distance;
    for(int i = 0; i < NUM_P; i++)
    {
        for(int j = 0; j < NUM_P; j++)
        {
            if(i != j)
            {
                distance = pow(particle[i]->x - particle[j]->x, 2);
                distance += pow(particle[i]->x - particle[j]->x, 2);
                distance += pow(particle[i]->x - particle[j]->x, 2);
                distance = sqrt(distance);
                acceleration = (particle[i]->mass)/distance;
                qDebug() << acceleration;
                //particle[j]->speed += acceleration/60;
            }
        }
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
