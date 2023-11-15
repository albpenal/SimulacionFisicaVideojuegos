#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
using namespace std;

class GravityForceGenerator :
    public ForceGenerator
{
protected:
    Vector3 _gravity;
public:
    GravityForceGenerator(const Vector3& g) :_gravity(g) {}
    virtual void updateForce(particle* particle, double t);
};

