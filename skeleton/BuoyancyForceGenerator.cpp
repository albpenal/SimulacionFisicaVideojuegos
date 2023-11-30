#include "BuoyancyForceGenerator.h"

BuoyancyForceGenerator::BuoyancyForceGenerator(float Height, float Volume, float LiquidDensity) {
	height = Height;
	volume = Volume;
	liquidDensity = LiquidDensity;
	Vector3 null = Vector3(0, 0, 0);
	liquidParticle = new particle(PxTransform(0, 0, 0), null, null, null, 1e6, 0.9, Vector4(0.6, 0.6, 0.6, 0.7), 100, true);
}

BuoyancyForceGenerator::~BuoyancyForceGenerator() {
	delete(liquidParticle);
}

void BuoyancyForceGenerator::updateForce(particle* particle, double t) {
	const float h = particle->getPos()->p.y;
	const float h0 = liquidParticle->getPos()->p.y;

	Vector3 BuoyancyForce(0, 0, 0);
	float inmersed = 0.0f;
	if (h - h0 > height * 0.5f) {
		inmersed = 0.0f;
	}
	else if (h0 - h > height * 0.5f) {
		inmersed = 1.0f;
	}
	else {
		inmersed = (h0 - h) / height + 0.5f;
	}

	BuoyancyForce.y = liquidDensity * volume * inmersed * gravity;

	particle->addForce(BuoyancyForce);
}