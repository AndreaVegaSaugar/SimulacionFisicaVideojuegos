#pragma once
#include "SpringForceGenerator.h"

class AnchoredSpring : public SpringForceGenerator
{
public:
	AnchoredSpring(double k, double resting, const Vector3& anchor_pos);
	inline void addK(double k) { _k += k; };
	~AnchoredSpring();

private:
	int time;
};

