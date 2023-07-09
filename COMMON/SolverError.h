#ifndef SOLVERERROR_H
#define SOLVERERROR_H

#include <string>

class SolverError
{
public:
	std::string what;

	SolverError();
	SolverError(std::string what);
	~SolverError();
};

#endif
