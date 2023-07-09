#ifndef CUBEERROR_H
#define CUBEERROR_H

#include <string>

class CubeError{
public:
	std::string what;

	CubeError();
	CubeError(std::string what);

	~CubeError();
};

#endif