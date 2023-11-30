#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class BuoyancyForceGenerator : public ForceGenerator {
protected:
	float height, volume, liquidDensity, gravity = 9.8;
	particle* liquidParticle;

public:
	BuoyancyForceGenerator(float Height, float Volume, float LiquidDensity);
	~BuoyancyForceGenerator();
	
	virtual void updateForce(particle* particle, double t);
};