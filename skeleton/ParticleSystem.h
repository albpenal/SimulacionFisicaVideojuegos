#pragma once
#include <list>
#include "particle.h"
#include "Firework.h"
#include "ParticleForceRegistry.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "VortexForceGenerator.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpring.h"
#include "BuoyancyForceGenerator.h"
using namespace std;

class ParticleSystem
{
private:
	AnchoredSpring* f3;
	ParticleForceRegistry* forceRegistry;
	list<particle*> particles;
	list<Firework*> fireworks;

public:
	enum SPRING { NORMAL, STATIC, SLINKY };
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
	void generateSpringDemo(SPRING type);
	void deleteAllParticles();
	void changeK(int k);
	void generateBuoyancy();
};

