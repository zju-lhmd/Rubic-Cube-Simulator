#ifndef REDUCEFILTER_H
#define REDUCEFILTER_H

#include <vector>

#include "../../COMMON/utilities.h" // common
#include "../../COMMON/types.h" // common
#include "../../COMMON/macro.h" // common

class ReduceFilter {
public:
	static CubeSteps Filter(CubeSteps&);

private:
	static bool ReduceContinuous(CubeSteps&);
	static bool ReduceInverse(CubeSteps&);
};

#endif