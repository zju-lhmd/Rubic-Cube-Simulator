#include "utilities.h"

char toUpper(char c)
{
	return c & ~32;
}

char toLower(char c)
{
	return c | 32;
}

std::string toUpperString(std::string str)
{
	transform(str.begin(), str.end(), str.begin(), toUpper);
	return str;
}

std::string toLowerString(std::string str)
{
	transform(str.begin(), str.end(), str.begin(), toLower);
	return str;
}

std::string stepsToString(CubeSteps steps, char delim)
{
	std::string r;
	ptrdiff_t size = steps.size();
	for (ptrdiff_t i = 0; i < size; ++i) {
		r += CubeRotateMethodName[steps[i]] + delim;
	}
	return r;
}

CubeRotateMethod inverse(CubeRotateMethod m)
{
	if (m < ROTATE_NONEi) {
		return (CubeRotateMethod)(m + (ROTATE_NONEi - ROTATE_NONE)); //inverse
	}else {
		return (CubeRotateMethod)(m - (ROTATE_NONEi - ROTATE_NONE)); //inverse
	}
}

void copySteps(CubeSteps &src, CubeSteps &dest)
{
	size_t size = src.size();
	for (ptrdiff_t i = 0; i < (ptrdiff_t)size; ++i) {
		if (src[i] != ROTATE_NONE && src[i] != ROTATE_NONEi)
			dest.push_back(src[i]);
	}
}

bool isWholeRotate(CubeRotateMethod m)
{
	return (m >= ROTATE_WHOLEX && m <= ROTATE_WHOLEZ) || (m >= ROTATE_WHOLEXi && m <= ROTATE_WHOLEZi);
}
