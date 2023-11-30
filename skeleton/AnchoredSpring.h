#pragma once
#include "SpringForceGenerator.h"
#include "core.hpp"
class AnchoredSpring : public SpringForceGenerator
{
public:
	AnchoredSpring(double k, double resting, const Vector3& anchorPos);
	~AnchoredSpring();
};

