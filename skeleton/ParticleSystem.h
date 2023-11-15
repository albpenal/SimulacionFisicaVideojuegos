#pragma once
#include <list>
#include "particle.h"
#include "Firework.h"
#include "ParticleForceRegistry.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "VortexForceGenerator.h"
using namespace std;

class ParticleSystem
{
private:
	ParticleForceRegistry* forceRegistry;
	list<particle*> particles;
	list<Firework*> fireworks;

public:
	ParticleSystem();
	~ParticleSystem();
	void update(float t);
	void FireUpdate(float t);
	void PartUpdate(float t);
	void addParticle(particle* p);
	void addFirework(Firework* f);
	void applyGravity(Vector3 g);
	void applyWind(Vector3 w);
	void applyVortex(Vector3 vort);
	void applyExplosion();
	void deleteAllParticles();
};

