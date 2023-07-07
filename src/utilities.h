#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "stdafx.h"
// #include "Cube.h"
// #include "CubeSolver.h"
// #include "GeneralSolver.h"
// #include "CubeError.h"
// #include "SolverError.h"
#include "../MODEL/Cube.h"
#include "../VIEWMODEL/CubeSolver.h"
#include "../VIEWMODEL/GeneralSolver.h"
#include "../MODEL/CubeError.h"
#include "../VIEWMODEL/SolverError.h"

vector<string> split(const string&, char);
char toUpper(char);
char toLower(char);
string toUpperString(string);
string toLowerString(string);
string stepsToString(CubeSteps&, char);
void printError(CubeError);
void printError(SolverError);
void randomCube(Cube&);
string randomCube();
CubeRotateMethod inverse(CubeRotateMethod);

// copy steps with deleting NONE steps
void copySteps(CubeSteps &src, CubeSteps &dest);

bool isWholeRotate(CubeRotateMethod);

//// format2: see pair 1
string convertFromFormat2(char*);
char *convertToFormat2(string);
CubeSolver *newSolver(Cube&);

#endif