#ifndef CUBEERROR_H
#define CUBEERROR_H

#include <string>

class CubeError {
public:
	std::string what; // error message

	CubeError() {}
	CubeError(std::string what): what(what) {}

	~CubeError() {}
};

#endif