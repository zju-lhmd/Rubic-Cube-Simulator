#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <algorithm>

#include "types.h" // common
#include "CubeError.h" // common

char toUpper(char);
char toLower(char);
std::string toUpperString(std::string);
std::string toLowerString(std::string);
std::string stepsToString(CubeSteps, char);
CubeRotateMethod inverse(CubeRotateMethod);
double GetTime();

// copy steps with deleting NONE steps
void copySteps(CubeSteps &src, CubeSteps &dest);

bool isWholeRotate(CubeRotateMethod);


#endif