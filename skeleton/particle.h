#pragma once
#include "RenderUtils.hpp"
#include <iostream>
using namespace physx;
// La clase particle representa una partícula en la simulación.
class particle
{
private:
    Vector3 v;        
    PxTransform p; 
    RenderItem* rend; 
    Vector3 acceleration;    
    float damp;     
    float mass;            
    bool dest = false; 

public:
    particle(PxTransform pos, Vector3 vel, Vector3 acc, float weight, float damping, Vector4 c, float radius);
    ~particle();

    void update(double t);

    void integrate(double t);

    RenderItem* getRend() const { return rend; }
    PxTransform* getPos() { return &p; }
};
