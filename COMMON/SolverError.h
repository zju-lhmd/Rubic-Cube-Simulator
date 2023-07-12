#ifndef SOLVERERROR_H
#define SOLVERERROR_H

#include <string>

class SolverError
{
public:
	std::string what; // error message

	SolverError() {}
	SolverError(std::string what): what(what) {}

	~SolverError() {}
};

#endif
