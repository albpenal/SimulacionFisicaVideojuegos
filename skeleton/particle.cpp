#include "particle.h"

particle::particle(PxTransform pos, Vector3 vel, Vector3 acc, float weight, float damping, Vector4 c, float radius)
    : p(pos), v(vel), acceleration(acc), mass(weight), damp(damping)
{
    rend = new RenderItem();
    rend->color = c;
    rend->shape = CreateShape(physx::PxSphereGeometry(radius));
    rend->transform = &p;
}

particle::~particle()
{
    DeregisterRenderItem(rend);
    delete rend;
}

void particle::update(double t)
{
    integrate(t);
}


void particle::integrate(double t)
{
    v += acceleration * t;
    v *= pow(damp, t);
    p.p += v * t; 
}

