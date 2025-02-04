#include "particle.h"

particle::particle(PxTransform pos, Vector3 vel, Vector3 acc, Vector3 grav, float weight, float damping, Vector4 c, float radius, bool box, bool lF)
    : p(pos), v(vel), acceleration(acc), gravity(grav), mass(weight), damp(damping), lF(lF)
{
    rend = new RenderItem();
    force = Vector3(0, 0, 0);
    rend->color = c;
    if (!box) rend->shape = CreateShape(physx::PxSphereGeometry(radius));
    else rend->shape = CreateShape(physx::PxBoxGeometry(radius, radius, radius));
    rend->transform = &p;
    RegisterRenderItem(rend);
}

particle::particle(PxTransform pos) : p(pos)
{
    force = Vector3(0, 0, 0);
    int r = rand() % 3;
    if (r == 0) setupCanonball();
    else if (r == 1) setupLaser();
    else setupFireball();
    rend = new RenderItem();
    rend->color = color;
    rend->shape = CreateShape(physx::PxSphereGeometry(radius));
    rend->transform = &p;
    RegisterRenderItem(rend);
}

void particle::setupFireball() {
    v = RandVect(5);
    acceleration = Vector3(0, 0, 0);
    gravity = Vector3(0, 1, 0);
    mass = 0.1f;
    damp = 0.9f;
    color = Vector4(1, 1, 0.5, 1);
    radius = 0.6f;
}

void particle::setupCanonball() {
    v = RandVect(8);
    acceleration = Vector3(0, 0, 0);
    gravity = Vector3(0, -9.8, 0);
    mass = 1.0f;
    damp = 0.9f;
    color = Vector4(1, 1, 0.2, 1);
    radius = 1.0f;
}

void particle::setupLaser() {
    v = RandVect(25);
    acceleration = Vector3(0, 0, 0);
    gravity = Vector3(0, -0.2, 0);
    mass = 0.01f;
    damp = 0.9f;
    color = Vector4(1, 1, 0.8, 1);
    radius = 0.3f;
}

Vector3 particle::RandVect(int size) {
    Vector3 v = Vector3(rand() % size - (size / 2), rand() % size - (size / 2), rand() % size - (size / 2));
    return v;
}
particle::~particle()
{
    DeregisterRenderItem(rend);
    delete rend;
}

void particle::update(double t)
{
    integrate(t);
    if (lF) {
        //tiempo de vida (si es mayor que 5 segundos se borra)  
        lifetime += t;
        //comprobar si se tiene que borrar
        if (lifetime >= 5) dest = true;
    }
    
}


void particle::integrate(double t)
{
    p.p += v * t;
    v += (force/mass) * t;
    v *= pow(damp, t);
    force *= 0.0;
}

