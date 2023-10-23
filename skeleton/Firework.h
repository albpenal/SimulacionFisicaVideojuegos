#pragma once
#include "RenderUtils.hpp"
#include <iostream>
#include "particle.h"
using namespace physx;
class ParticleGenerator;
class ParticleSystem;
class Firework
{
private:
    ParticleSystem* partS;
    ParticleGenerator* partG;
    Vector3 v;
    PxTransform p;
    RenderItem* rend;
    Vector3 acceleration, gravity;
    Vector4 color;
    float damp, r, mass;
    float lifetime = 0.0f;
    bool dest = false;
    int generation;
public:
    Firework(PxTransform pos, Vector3 vel, Vector3 acc, Vector3 grav, float weight, float damping, Vector4 c, float radius, ParticleSystem* pS, ParticleGenerator* pG, int gen = 3);
    ~Firework();

    void update(double t);
    void integrate(double t);
    void OnDie(int n);
    RenderItem* getRend() const { return rend; }
    PxTransform* getPos() { return &p; }
    bool getDestroyed() { return dest; }
};

