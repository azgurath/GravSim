#ifndef PARTICLE_H
#define PARTICLE_H


class Particle
{
public:
    Particle();

    float x, y, z; // position
    float angX, angY, angZ; // velocity vector
    float mass; // mass
};

#endif // PARTICLE_H
