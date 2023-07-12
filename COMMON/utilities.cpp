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
