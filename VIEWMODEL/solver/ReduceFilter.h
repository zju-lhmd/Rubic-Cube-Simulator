#ifndef REDUCEFILTER_H
#define REDUCEFILTER_H

#include <vector>

#include "../../COMMON/utilities.h" // common
#include "../../COMMON/types.h" // common
#include "../../COMMON/macro.h" // common

class ReduceFilter {
public:
	CubeSteps Filter(CubeSteps&);

private:
	bool ReduceContinuous(CubeSteps&);
	bool ReduceInverse(CubeSteps&);
	CubeRotateMethod inverse(CubeRotateMethod m);
	void copySteps(CubeSteps &src, CubeSteps &dest);
};

#endif