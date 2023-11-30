#include "AnchoredSpring.h"

AnchoredSpring::AnchoredSpring(double k, double resting, const Vector3& anchorPos) :
	SpringForceGenerator(k, resting, nullptr){
	Vector3 null = Vector3(0, 0, 0);
	_other = new particle(PxTransform(anchorPos), null, null, null, 1e6,0.9, Vector4(0.6, 0.6, 0.6, 1), 1, true);
}

AnchoredSpring::~AnchoredSpring() {
	delete _other;
}