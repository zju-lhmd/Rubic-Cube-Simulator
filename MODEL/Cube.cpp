#include "Cube.h"

Cube::Cube()
{
    // Initializing the initial state of the cube，with hexadecimal
	subCubes.resize(RANK); oldSubCubes.resize(RANK);
	for(int i = 0;i < RANK;++i) {
		subCubes[i].resize(RANK); oldSubCubes[i].resize(RANK);
		for(int j = 0;j < RANK;++j) {
			subCubes[i][j].resize(RANK); oldSubCubes[i][j].resize(RANK);
		}
	}
	// Init cube state
	Init();
}

Cube::Cube(const Cube &b)
    : subCubes(b.subCubes), oldSubCubes(b.oldSubCubes)
{
}

Cube::~Cube()
{
}

void Cube::Init() {
// Initializing the initial state of the cube，with hexadecimal
    // first layer
    subCubes[0][0][0] = 0x063002;
    subCubes[1][0][0] = 0x060002;
    subCubes[2][0][0] = 0x060402;
    subCubes[0][0][1] = 0x003002;
    subCubes[1][0][1] = 0x000002;
    subCubes[2][0][1] = 0x000402;
    subCubes[0][0][2] = 0x503002;
    subCubes[1][0][2] = 0x500002;
    subCubes[2][0][2] = 0x500402;
    // second layer
    subCubes[0][1][0] = 0x063000;
    subCubes[1][1][0] = 0x060000;
    subCubes[2][1][0] = 0x060400;
    subCubes[0][1][1] = 0x003000;
    subCubes[1][1][1] = 0x000000;
    subCubes[2][1][1] = 0x000400;
    subCubes[0][1][2] = 0x503000;
    subCubes[1][1][2] = 0x500000;
    subCubes[2][1][2] = 0x500400;
    // third layer
    subCubes[0][2][0] = 0x063010;
    subCubes[1][2][0] = 0x060010;
    subCubes[2][2][0] = 0x060410;
    subCubes[0][2][1] = 0x003010;
    subCubes[1][2][1] = 0x000010;
    subCubes[2][2][1] = 0x000410;
    subCubes[0][2][2] = 0x503010;
    subCubes[1][2][2] = 0x500010;
    subCubes[2][2][2] = 0x500410;
}

cubes_t Cube::GetCubes()
{
    return subCubes;
}

void Cube::randomCube()
{
	return;
}

void Cube::Deserialize(std::string data)
{
	return;
}

std::string Cube::Serialize()
{
	return "";
}

void Cube::SaveState()
{
    oldSubCubes = subCubes;
}

void Cube::DoMethod(CubeRotateMethod method)
{
    // Perform a cube rotation based on the given method
    switch (method) {
        case ROTATE_NONE: // down through
        case ROTATE_NONEi: break;
        case ROTATE_FRONT: F(); break;
        case ROTATE_BACK: B(); break;
        case ROTATE_LEFT: L(); break;
        case ROTATE_RIGHT: R(); break;
        case ROTATE_UP: U(); break;
        case ROTATE_DOWN: D(); break;
        case ROTATE_FRONTi: Fi(); break;
        case ROTATE_BACKi: Bi(); break;
        case ROTATE_LEFTi: Li(); break;
        case ROTATE_RIGHTi: Ri(); break;
        case ROTATE_UPi: Ui(); break;
        case ROTATE_DOWNi: Di(); break;
        case ROTATE_WHOLEX: RotateUp(); break;
        case ROTATE_WHOLEY: RotateLeft(); break;
        case ROTATE_WHOLEZ: RotateClockwise(); break;
        case ROTATE_WHOLEXi: RotateDown(); break;
        case ROTATE_WHOLEYi: RotateRight(); break;
        case ROTATE_WHOLEZi: RotateCounterClockwise(); break;
        default: break;
	}
}

// Functions for individual cube rotations
void Cube::R()
{
    // Perform a rotation on the right face of the cube
	SaveState();
	subCubes[2][0][0] = ROTATE_UP(oldSubCubes[2][2][0]);
	subCubes[2][0][1] = ROTATE_UP(oldSubCubes[2][1][0]);
	subCubes[2][0][2] = ROTATE_UP(oldSubCubes[2][0][0]);
	subCubes[2][1][0] = ROTATE_UP(oldSubCubes[2][2][1]);
	subCubes[2][1][1] = ROTATE_UP(oldSubCubes[2][1][1]);
	subCubes[2][1][2] = ROTATE_UP(oldSubCubes[2][0][1]);
	subCubes[2][2][0] = ROTATE_UP(oldSubCubes[2][2][2]);
	subCubes[2][2][1] = ROTATE_UP(oldSubCubes[2][1][2]);
	subCubes[2][2][2] = ROTATE_UP(oldSubCubes[2][0][2]);
}

void Cube::Ri()
{
    // Perform a counter-clockwise rotation on the right face of the cube
	SaveState();
	subCubes[2][0][0] = ROTATE_DOWN(oldSubCubes[2][0][2]);
	subCubes[2][0][1] = ROTATE_DOWN(oldSubCubes[2][1][2]);
	subCubes[2][0][2] = ROTATE_DOWN(oldSubCubes[2][2][2]);
	subCubes[2][1][0] = ROTATE_DOWN(oldSubCubes[2][0][1]);
	subCubes[2][1][1] = ROTATE_DOWN(oldSubCubes[2][1][1]);
	subCubes[2][1][2] = ROTATE_DOWN(oldSubCubes[2][2][1]);
	subCubes[2][2][0] = ROTATE_DOWN(oldSubCubes[2][0][0]);
	subCubes[2][2][1] = ROTATE_DOWN(oldSubCubes[2][1][0]);
	subCubes[2][2][2] = ROTATE_DOWN(oldSubCubes[2][2][0]);
}

void Cube::L()
{
    // Perform a rotation on the left face of the cube
	SaveState();
	subCubes[0][0][0] = ROTATE_DOWN(oldSubCubes[0][0][2]);
	subCubes[0][0][1] = ROTATE_DOWN(oldSubCubes[0][1][2]);
	subCubes[0][0][2] = ROTATE_DOWN(oldSubCubes[0][2][2]);
	subCubes[0][1][0] = ROTATE_DOWN(oldSubCubes[0][0][1]);
	subCubes[0][1][1] = ROTATE_DOWN(oldSubCubes[0][1][1]);
	subCubes[0][1][2] = ROTATE_DOWN(oldSubCubes[0][2][1]);
	subCubes[0][2][0] = ROTATE_DOWN(oldSubCubes[0][0][0]);
	subCubes[0][2][1] = ROTATE_DOWN(oldSubCubes[0][1][0]);
	subCubes[0][2][2] = ROTATE_DOWN(oldSubCubes[0][2][0]);
}

void Cube::Li()
{
    // Perform a counter-clockwise rotation on the left face of the cube
	SaveState();
	subCubes[0][0][0] = ROTATE_UP(oldSubCubes[0][2][0]);
	subCubes[0][0][1] = ROTATE_UP(oldSubCubes[0][1][0]);
	subCubes[0][0][2] = ROTATE_UP(oldSubCubes[0][0][0]);
	subCubes[0][1][0] = ROTATE_UP(oldSubCubes[0][2][1]);
	subCubes[0][1][1] = ROTATE_UP(oldSubCubes[0][1][1]);
	subCubes[0][1][2] = ROTATE_UP(oldSubCubes[0][0][1]);
	subCubes[0][2][0] = ROTATE_UP(oldSubCubes[0][2][2]);
	subCubes[0][2][1] = ROTATE_UP(oldSubCubes[0][1][2]);
	subCubes[0][2][2] = ROTATE_UP(oldSubCubes[0][0][2]);
}

void Cube::B()
{
    // Perform a rotation on the back face of the cube
	SaveState();
	subCubes[0][0][0] = ROTATE_CCLK(oldSubCubes[0][2][0]);
	subCubes[1][0][0] = ROTATE_CCLK(oldSubCubes[0][1][0]);
	subCubes[2][0][0] = ROTATE_CCLK(oldSubCubes[0][0][0]);
	subCubes[0][1][0] = ROTATE_CCLK(oldSubCubes[1][2][0]);
	subCubes[1][1][0] = ROTATE_CCLK(oldSubCubes[1][1][0]);
	subCubes[2][1][0] = ROTATE_CCLK(oldSubCubes[1][0][0]);
	subCubes[0][2][0] = ROTATE_CCLK(oldSubCubes[2][2][0]);
	subCubes[1][2][0] = ROTATE_CCLK(oldSubCubes[2][1][0]);
	subCubes[2][2][0] = ROTATE_CCLK(oldSubCubes[2][0][0]);
}

void Cube::Bi()
{
    // Perform a counter-clockwise rotation on the back face of the cube
	SaveState();
	subCubes[0][0][0] = ROTATE_CLK(oldSubCubes[2][0][0]);
	subCubes[1][0][0] = ROTATE_CLK(oldSubCubes[2][1][0]);
	subCubes[2][0][0] = ROTATE_CLK(oldSubCubes[2][2][0]);
	subCubes[0][1][0] = ROTATE_CLK(oldSubCubes[1][0][0]);
	subCubes[1][1][0] = ROTATE_CLK(oldSubCubes[1][1][0]);
	subCubes[2][1][0] = ROTATE_CLK(oldSubCubes[1][2][0]);
	subCubes[0][2][0] = ROTATE_CLK(oldSubCubes[0][0][0]);
	subCubes[1][2][0] = ROTATE_CLK(oldSubCubes[0][1][0]);
	subCubes[2][2][0] = ROTATE_CLK(oldSubCubes[0][2][0]);
}

void Cube::D()
{
    // Perform a rotation on the down face of the cube
	SaveState();
	subCubes[0][0][0] = ROTATE_RIGHT(oldSubCubes[2][0][0]);
	subCubes[1][0][0] = ROTATE_RIGHT(oldSubCubes[2][0][1]);
	subCubes[2][0][0] = ROTATE_RIGHT(oldSubCubes[2][0][2]);
	subCubes[0][0][1] = ROTATE_RIGHT(oldSubCubes[1][0][0]);
	subCubes[1][0][1] = ROTATE_RIGHT(oldSubCubes[1][0][1]);
	subCubes[2][0][1] = ROTATE_RIGHT(oldSubCubes[1][0][2]);
	subCubes[0][0][2] = ROTATE_RIGHT(oldSubCubes[0][0][0]);
	subCubes[1][0][2] = ROTATE_RIGHT(oldSubCubes[0][0][1]);
	subCubes[2][0][2] = ROTATE_RIGHT(oldSubCubes[0][0][2]);
}

void Cube::Di()
{
    // Perform a counter-clockwise rotation on the down face of the cube
	SaveState();
	subCubes[0][0][0] = ROTATE_LEFT(oldSubCubes[0][0][2]);
	subCubes[1][0][0] = ROTATE_LEFT(oldSubCubes[0][0][1]);
	subCubes[2][0][0] = ROTATE_LEFT(oldSubCubes[0][0][0]);
	subCubes[0][0][1] = ROTATE_LEFT(oldSubCubes[1][0][2]);
	subCubes[1][0][1] = ROTATE_LEFT(oldSubCubes[1][0][1]);
	subCubes[2][0][1] = ROTATE_LEFT(oldSubCubes[1][0][0]);
	subCubes[0][0][2] = ROTATE_LEFT(oldSubCubes[2][0][2]);
	subCubes[1][0][2] = ROTATE_LEFT(oldSubCubes[2][0][1]);
	subCubes[2][0][2] = ROTATE_LEFT(oldSubCubes[2][0][0]);
}

void Cube::F()
{
    // Perform a rotation on the front face of the cube
	SaveState();
	subCubes[0][0][2] = ROTATE_CLK(oldSubCubes[2][0][2]);
	subCubes[1][0][2] = ROTATE_CLK(oldSubCubes[2][1][2]);
	subCubes[2][0][2] = ROTATE_CLK(oldSubCubes[2][2][2]);
	subCubes[0][1][2] = ROTATE_CLK(oldSubCubes[1][0][2]);
	subCubes[1][1][2] = ROTATE_CLK(oldSubCubes[1][1][2]);
	subCubes[2][1][2] = ROTATE_CLK(oldSubCubes[1][2][2]);
	subCubes[0][2][2] = ROTATE_CLK(oldSubCubes[0][0][2]);
	subCubes[1][2][2] = ROTATE_CLK(oldSubCubes[0][1][2]);
	subCubes[2][2][2] = ROTATE_CLK(oldSubCubes[0][2][2]);
}

void Cube::Fi()
{
    // Perform a counter-clockwise rotation on the front face of the cube
	SaveState();
	subCubes[0][0][2] = ROTATE_CCLK(oldSubCubes[0][2][2]);
	subCubes[1][0][2] = ROTATE_CCLK(oldSubCubes[0][1][2]);
	subCubes[2][0][2] = ROTATE_CCLK(oldSubCubes[0][0][2]);
	subCubes[0][1][2] = ROTATE_CCLK(oldSubCubes[1][2][2]);
	subCubes[1][1][2] = ROTATE_CCLK(oldSubCubes[1][1][2]);
	subCubes[2][1][2] = ROTATE_CCLK(oldSubCubes[1][0][2]);
	subCubes[0][2][2] = ROTATE_CCLK(oldSubCubes[2][2][2]);
	subCubes[1][2][2] = ROTATE_CCLK(oldSubCubes[2][1][2]);
	subCubes[2][2][2] = ROTATE_CCLK(oldSubCubes[2][0][2]);
}

void Cube::U()
{
    // Perform a rotation on the up face of the cube
	SaveState();
	subCubes[0][2][0] = ROTATE_LEFT(oldSubCubes[0][2][2]);
	subCubes[1][2][0] = ROTATE_LEFT(oldSubCubes[0][2][1]);
	subCubes[2][2][0] = ROTATE_LEFT(oldSubCubes[0][2][0]);
	subCubes[0][2][1] = ROTATE_LEFT(oldSubCubes[1][2][2]);
	subCubes[1][2][1] = ROTATE_LEFT(oldSubCubes[1][2][1]);
	subCubes[2][2][1] = ROTATE_LEFT(oldSubCubes[1][2][0]);
	subCubes[0][2][2] = ROTATE_LEFT(oldSubCubes[2][2][2]);
	subCubes[1][2][2] = ROTATE_LEFT(oldSubCubes[2][2][1]);
	subCubes[2][2][2] = ROTATE_LEFT(oldSubCubes[2][2][0]);
}

void Cube::Ui()
{
    // Perform a counter-clockwise rotation on the up face of the cube
	SaveState();
	subCubes[0][2][0] = ROTATE_RIGHT(oldSubCubes[2][2][0]);
	subCubes[1][2][0] = ROTATE_RIGHT(oldSubCubes[2][2][1]);
	subCubes[2][2][0] = ROTATE_RIGHT(oldSubCubes[2][2][2]);
	subCubes[0][2][1] = ROTATE_RIGHT(oldSubCubes[1][2][0]);
	subCubes[1][2][1] = ROTATE_RIGHT(oldSubCubes[1][2][1]);
	subCubes[2][2][1] = ROTATE_RIGHT(oldSubCubes[1][2][2]);
	subCubes[0][2][2] = ROTATE_RIGHT(oldSubCubes[0][2][0]);
	subCubes[1][2][2] = ROTATE_RIGHT(oldSubCubes[0][2][1]);
	subCubes[2][2][2] = ROTATE_RIGHT(oldSubCubes[0][2][2]);
}

void Cube::RotateLeft()
{
	U();// Rotate the Up face clockwise
	SaveState();
    // Rotate the left face clockwise
	subCubes[0][1][0] = ROTATE_LEFT(oldSubCubes[0][1][2]);
	subCubes[1][1][0] = ROTATE_LEFT(oldSubCubes[0][1][1]);
	subCubes[2][1][0] = ROTATE_LEFT(oldSubCubes[0][1][0]);
	subCubes[0][1][1] = ROTATE_LEFT(oldSubCubes[1][1][2]);
	subCubes[1][1][1] = ROTATE_LEFT(oldSubCubes[1][1][1]);
	subCubes[2][1][1] = ROTATE_LEFT(oldSubCubes[1][1][0]);
	subCubes[0][1][2] = ROTATE_LEFT(oldSubCubes[2][1][2]);
	subCubes[1][1][2] = ROTATE_LEFT(oldSubCubes[2][1][1]);
	subCubes[2][1][2] = ROTATE_LEFT(oldSubCubes[2][1][0]);
	Di();// Rotate the Down face counter-clockwise
}

void Cube::RotateRight()
{
	Ui();// Rotate the Up face counter-clockwise
	SaveState();
    // Rotate the right face clockwise
	subCubes[0][1][0] = ROTATE_RIGHT(oldSubCubes[2][1][0]);
	subCubes[1][1][0] = ROTATE_RIGHT(oldSubCubes[2][1][1]);
	subCubes[2][1][0] = ROTATE_RIGHT(oldSubCubes[2][1][2]);
	subCubes[0][1][1] = ROTATE_RIGHT(oldSubCubes[1][1][0]);
	subCubes[1][1][1] = ROTATE_RIGHT(oldSubCubes[1][1][1]);
	subCubes[2][1][1] = ROTATE_RIGHT(oldSubCubes[1][1][2]);
	subCubes[0][1][2] = ROTATE_RIGHT(oldSubCubes[0][1][0]);
	subCubes[1][1][2] = ROTATE_RIGHT(oldSubCubes[0][1][1]);
	subCubes[2][1][2] = ROTATE_RIGHT(oldSubCubes[0][1][2]);
	D();// Rotate the Down face clockwise

}

void Cube::RotateUp()
{
	Li();// Rotate the Left face counter-clockwise
	SaveState();
    // Rotate the Up face clockwise
	subCubes[1][0][0] = ROTATE_UP(oldSubCubes[1][2][0]);
	subCubes[1][0][1] = ROTATE_UP(oldSubCubes[1][1][0]);
	subCubes[1][0][2] = ROTATE_UP(oldSubCubes[1][0][0]);
	subCubes[1][1][0] = ROTATE_UP(oldSubCubes[1][2][1]);
	subCubes[1][1][1] = ROTATE_UP(oldSubCubes[1][1][1]);
	subCubes[1][1][2] = ROTATE_UP(oldSubCubes[1][0][1]);
	subCubes[1][2][0] = ROTATE_UP(oldSubCubes[1][2][2]);
	subCubes[1][2][1] = ROTATE_UP(oldSubCubes[1][1][2]);
	subCubes[1][2][2] = ROTATE_UP(oldSubCubes[1][0][2]);
	R();// Rotate the Right face clockwise
}

void Cube::RotateDown()
{
	L();// Rotate the Left face clockwise
	SaveState();
    // Rotate the Down face clockwise
	subCubes[1][0][0] = ROTATE_DOWN(oldSubCubes[1][0][2]);
	subCubes[1][0][1] = ROTATE_DOWN(oldSubCubes[1][1][2]);
	subCubes[1][0][2] = ROTATE_DOWN(oldSubCubes[1][2][2]);
	subCubes[1][1][0] = ROTATE_DOWN(oldSubCubes[1][0][1]);
	subCubes[1][1][1] = ROTATE_DOWN(oldSubCubes[1][1][1]);
	subCubes[1][1][2] = ROTATE_DOWN(oldSubCubes[1][2][1]);
	subCubes[1][2][0] = ROTATE_DOWN(oldSubCubes[1][0][0]);
	subCubes[1][2][1] = ROTATE_DOWN(oldSubCubes[1][1][0]);
	subCubes[1][2][2] = ROTATE_DOWN(oldSubCubes[1][2][0]);
	Ri();// Rotate the Right face counter-clockwise
}

void Cube::RotateClockwise()
{
	F();// Rotate the Front face clockwise
	SaveState();
    // Rotate the Up face clockwise
	subCubes[0][0][1] = ROTATE_CLK(oldSubCubes[2][0][1]);
	subCubes[1][0][1] = ROTATE_CLK(oldSubCubes[2][1][1]);
	subCubes[2][0][1] = ROTATE_CLK(oldSubCubes[2][2][1]);
	subCubes[0][1][1] = ROTATE_CLK(oldSubCubes[1][0][1]);
	subCubes[1][1][1] = ROTATE_CLK(oldSubCubes[1][1][1]);
	subCubes[2][1][1] = ROTATE_CLK(oldSubCubes[1][2][1]);
	subCubes[0][2][1] = ROTATE_CLK(oldSubCubes[0][0][1]);
	subCubes[1][2][1] = ROTATE_CLK(oldSubCubes[0][1][1]);
	subCubes[2][2][1] = ROTATE_CLK(oldSubCubes[0][2][1]);
	Bi();// Rotate the Back face counter-clockwise
}

void Cube::RotateCounterClockwise()
{
	Fi();// Rotate the Front face counter-clockwise
	SaveState();
    // Rotate the Up face counter-clockwise
	subCubes[0][0][1] = ROTATE_CCLK(oldSubCubes[0][2][1]);
	subCubes[1][0][1] = ROTATE_CCLK(oldSubCubes[0][1][1]);
	subCubes[2][0][1] = ROTATE_CCLK(oldSubCubes[0][0][1]);
	subCubes[0][1][1] = ROTATE_CCLK(oldSubCubes[1][2][1]);
	subCubes[1][1][1] = ROTATE_CCLK(oldSubCubes[1][1][1]);
	subCubes[2][1][1] = ROTATE_CCLK(oldSubCubes[1][0][1]);
	subCubes[0][2][1] = ROTATE_CCLK(oldSubCubes[2][2][1]);
	subCubes[1][2][1] = ROTATE_CCLK(oldSubCubes[2][1][1]);
	subCubes[2][2][1] = ROTATE_CCLK(oldSubCubes[2][0][1]);
	B();// Rotate the Back face clockwise
}
