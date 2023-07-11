#include "CommandHandlers.h"

CommandHandler::CommandHandler(Cube* c)
	: cube(c)
{
	rotateController.SetCube(cube);
}

CommandHandler::~CommandHandler()
{
}

void CommandHandler::rotateHandler(std::string value)
{
	value = toUpperString(value);
	if (value.length() > 1)
		value[1] = toLower(value[1]);

	CubeRotateMethod method = NameToCubeRotateMethod[value];
	if (method != ROTATE_NONE) {
		rotateController.startRotate(method);
	}
}

void CommandHandler::resetHandler()
{
	cube->Init();
}

void CommandHandler::solveHandler()
{
	return;
}

void CommandHandler::stopHandler()
{
	return;
}

void CommandHandler::randomHandler()
{
	cube->randomCube();
}

void CommandHandler::loadHandler(std::string value)
{
	return;
}

void CommandHandler::saveHandler(std::string value)
{
	return;
}

void CommandHandler::testHandler()
{
	return;
}

bool CommandHandler::init()
{
    // Initialize randomize seeds
    srand(clock());
    return true;
}
