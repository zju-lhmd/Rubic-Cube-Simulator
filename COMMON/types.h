#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <map>
#include <string>

// cube_t format 0b ffff bbbb llll rrrr uuuu dddd
typedef unsigned int cube_t;

/**
 * Coordinate fomat
 *     Y
 *     |
 *     |
 *     |
 *     |________X
 *    /
 *   /
 *  /
 * Z
 */
//             X           Y           Z
typedef std::vector<std::vector<std::vector<cube_t>>> cubes_t;

enum CubeColor
{
	COLOR_UNUSED, // 0x0
	COLOR_WHITE, // 0x1
	COLOR_YELLOW, // 0x2
	COLOR_ORANGE, // 0x3
	COLOR_RED, // 0x4
	COLOR_GREEN, // 0x5
	COLOR_BLUE, // 0x6
	COLOR_INVALID = 0xF
};

// suffix 'i' means inverse direction, +10 -> i, -10 -> !i
enum CubeRotateMethod
{
	ROTATE_NONE,
	ROTATE_FRONT,
	ROTATE_BACK,
	ROTATE_LEFT,
	ROTATE_RIGHT,
	ROTATE_UP,
	ROTATE_DOWN,
	ROTATE_WHOLEX,  // whole up
	ROTATE_WHOLEY,  // whole left
	ROTATE_WHOLEZ,  // whole clockwise
	ROTATE_NONEi,
	ROTATE_FRONTi,
	ROTATE_BACKi,
	ROTATE_LEFTi,
	ROTATE_RIGHTi,
	ROTATE_UPi,
	ROTATE_DOWNi,
	ROTATE_WHOLEXi, // whole down
	ROTATE_WHOLEYi, // whole right
	ROTATE_WHOLEZi  // whole counter-clockwise
};

typedef std::vector<CubeRotateMethod> CubeSteps;


#endif