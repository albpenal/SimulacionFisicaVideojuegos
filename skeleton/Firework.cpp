#include "Firework.h"
#include "ParticleSystem.h"
#include "ParticleGenerator.h"

Firework::Firework(PxTransform pos, Vector3 vel, Vector3 acc, Vector3 grav, float weight, float damping, Vector4 c, float radius, ParticleSystem* pS, ParticleGenerator* pG, int gen)
    : p(pos), v(vel), acceleration(acc), gravity(grav), mass(weight), damp(damping), partS(pS), generation(gen), color(c), r(radius), partG(pG)
{
    rend = new RenderItem();
    rend->color = c;
    rend->shape = CreateShape(physx::PxSphereGeometry(radius));
    rend->transform = &p;
    RegisterRenderItem(rend);
}

Firework::~Firework()
{
    OnDie(3);
    DeregisterRenderItem(rend);
    delete rend;
}

void Firework::OnDie(int n) {
    Camera* camera = GetCamera();
    for (int i = 0; i < n; i++) {
        if (generation == 0) partG->generateParticle(p);
        else partG->generateFirework(p, v * 0.6, acceleration, gravity, mass, damp, Vector4(color.x,color.y, color.z *0.8, 1), r * 0.6, generation - 1);        
    }
}

void Firework::update(double t)
{
    integrate(t);
    //tiempo de vida (si es mayor que 5 segundos se borra)  
    lifetime += t;
    //comprobar si se tiene que borrar
    if (/*p.p.y < 20 ||*/ lifetime >= 2) dest = true;
}


void Firework::integrate(double t)
{
    p.p += v * t;
    v += (gravity + acceleration) * t;
    v *= pow(damp, t);
}