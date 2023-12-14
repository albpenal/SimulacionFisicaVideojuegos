#pragma once
#include "ForceGenerator.h"
#define M_PI 3.14159265358979323846


class ExplosionForceGenerator : public ForceGenerator {
public:
    ExplosionForceGenerator(const float k, const float r, const float t) : intensity(k), radius(r), timeConstant(t) {}

    virtual void updateForce(particle* particle, double t);
    virtual void updateForce(RigidBody* rb, double t);
protected:
    float intensity; // Intensity of the explosion
    float timeConstant; // Time constant for the force application
    float radius; // Radius of the explosion effect

private:
    float calculateDistance(Vector3 center, Vector3 position);
};
