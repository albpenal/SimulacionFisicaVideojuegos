#include "Firework.h"
#include "ParticleSystem.h"

Firework::Firework(PxTransform pos, Vector3 vel, Vector3 acc, Vector3 grav, float weight, float damping, Vector4 c, float radius, ParticleSystem* pS)
    : p(pos), v(vel), acceleration(acc), gravity(grav), mass(weight), damp(damping), partS(pS)
{
    rend = new RenderItem();
    rend->color = c;
    rend->shape = CreateShape(physx::PxSphereGeometry(radius));
    rend->transform = &p;
    RegisterRenderItem(rend);
}

Firework::~Firework()
{
    Camera* camera = GetCamera();
    particle* part = new particle(p);
    partS->addParticle(part);
    DeregisterRenderItem(rend);
    delete rend;
}

void Firework::update(double t)
{
    integrate(t);
    //tiempo de vida (si es mayor que 5 segundos se borra)  
    lifetime += t;
    //comprobar si se tiene que borrar
    if (p.p.y < 20 || lifetime >= 5) dest = true;
}


void Firework::integrate(double t)
{
    p.p += v * t;
    v += (gravity + acceleration) * t;
    v *= pow(damp, t);
}