#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
class SpringForceGenerator : public ForceGenerator
{
protected:
	double _k; //coeff
	double _resting_length;
	particle* _other;

public:
	SpringForceGenerator(double k, double resting_length, particle* other) :
		_k(k), _resting_length(resting_length), _other(other){}

	virtual void updateForce(particle* particle, double t);

	inline void setK(double k) { _k = k; }

	~SpringForceGenerator() {};
	particle* getOther() { return _other; }
};


