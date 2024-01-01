#pragma once
#include "DragGenerator.h"
class WindForceGenerator : public DragGenerator
{
public:
    WindForceGenerator(const Vector3& w, const float k1 = 0.25, const float k2 = 0);
    virtual void updateForce(particle* particle, double t);
    virtual void updateForce(RigidBody* rb, double t);
protected:
    Vector3 wind;
};

