#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Particle.h"
using namespace std;
class ForceGenerator {
public:
	virtual void updateForce(particle* particle, double duration = 0) = 0;
	virtual ~ForceGenerator() {}
};