#pragma once
#include "RenderUtils.hpp"
#include <iostream>
using namespace physx;
// La clase particle representa una partícula en la simulación.
class particle
{
private:
    Vector3 v;        
    Vector4 color;        
    PxTransform p; 
    RenderItem* rend; 
    Vector3 acceleration, gravity, force;    
    float radius;
    float damp;     
    float mass;
    float lifetime = 0.0f;
    bool dest = false; 
    bool lF; 

public:
    particle(PxTransform pos, Vector3 vel, Vector3 acc, Vector3 grav, float weight, float damping, Vector4 c, float radius, bool box = false, bool lF = true);
    particle(PxTransform pos);
    ~particle();

    void update(double t);

    void integrate(double t);
    Vector3 RandVect(int size);
    void setupFireball();
    void setupCanonball();
    void setupLaser();
    RenderItem* getRend() const { return rend; }
    PxTransform* getPos() { return &p; }
    Vector3 getVel() { return v; }
    bool getDestroyed() { return dest; }
    void addForce(Vector3 f) { force += f; }
    float getMass() { return mass; }
};
