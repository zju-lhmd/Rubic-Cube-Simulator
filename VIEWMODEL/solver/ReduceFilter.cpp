#include "ReduceFilter.h"

CubeSteps ReduceFilter::Filter(CubeSteps &steps)
{
	CubeSteps newSteps = steps;
	while (ReduceContinuous(newSteps) || ReduceInverse(newSteps)) {
		CubeSteps newNewSteps;
		copySteps(newSteps, newNewSteps);
		newSteps = newNewSteps;
	}
	return newSteps;
}

CubeRotateMethod ReduceFilter::inverse(CubeRotateMethod m)
{
	if (m < ROTATE_NONEi) {
		return (CubeRotateMethod)(m + (ROTATE_NONEi - ROTATE_NONE)); //inverse
	}else {
		return (CubeRotateMethod)(m - (ROTATE_NONEi - ROTATE_NONE)); //inverse
	}
}

void ReduceFilter::copySteps(CubeSteps &src, CubeSteps &dest)
{
	size_t size = src.size();
	for (ptrdiff_t i = 0; i < (ptrdiff_t)size; ++i) {
		if (src[i] != ROTATE_NONE && src[i] != ROTATE_NONEi)
			dest.push_back(src[i]);
	}
}

bool ReduceFilter::ReduceContinuous(CubeSteps &steps)
{
	size_t size = steps.size();
	bool found = false;
	for (ptrdiff_t i = 0; i < (ptrdiff_t)size - 2; ++i) {
		if (steps[i] == steps[i + 1] && steps[i] == steps[i + 2]) {
			steps[i] = inverse(steps[i]);
			steps[i + 1] = steps[i + 2] = ROTATE_NONE;
			found = true;
		}
	}
	return found;
}

bool ReduceFilter::ReduceInverse(CubeSteps &steps)
{
	size_t size = steps.size();
	bool found = false;
	for (ptrdiff_t i = 0; i < (ptrdiff_t)size - 1; ++i) {
		if (steps[i] == inverse(steps[i + 1])) {
			steps[i] = steps[i + 1] = ROTATE_NONE;
			found = true;
		}
	}
	return found;
}