#pragma once
#include "ForceGenerator.h"
using namespace std;
class DragGenerator : public ForceGenerator
{
public:
    DragGenerator(const float k1, const float k2) : _k1(k1), _k2(k2) {}
    virtual void updateForce(particle* particle, double t) {
        Vector3 v = particle->getVel();
        float dragcoef = v.normalize();
        Vector3 dragF;
        dragcoef = _k1 * dragcoef + _k2 * dragcoef * dragcoef;
        dragF = -v * dragcoef;
        particle->addForce(dragF);
    }
    inline void setDrag(float k1, float k2) { _k1 = k1; _k2 = k2; }
    inline float getK1() { return (_k1); }
    inline float getK2() { return (_k2); }
protected:
    float _k1; //Coef for velocity
    float _k2; //Coef for square velocity
};

