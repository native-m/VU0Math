#ifndef VECTORCONSTANTS_H
#define VECTORCONSTANTS_H

#include "VU0MathDefines.h"

namespace VU0Math
{

class VectorConstants
{
public:
	static const Vu0FVector vec4Zero;
	static const Vu0FVector vec4One;
};

const Vu0FVector VectorConstants::vec4Zero = { 0.f, 0.f, 0.f, 0.f };
const Vu0FVector VectorConstants::vec4One = { 1.f, 1.f, 1.f, 1.f };

}

#endif
