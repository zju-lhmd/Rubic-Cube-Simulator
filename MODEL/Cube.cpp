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
    for (int i = 0; i < rand() % 1000 + 1; ++i) {
        CubeRotateMethod method = (CubeRotateMethod)((rand() % 19) + 1);
        DoMethod(method);
    }
}

void Cube::Deserialize(std::string data)
{
	if (data.length() != FORMAT_LENGTH) {
		throw CubeError("Data length missmatch.");
	}
    // Deserializing the cube state from the given data string
	for (int z = 0; z < 3; ++z) {
		for (int y = 0; y < 3; ++y) {
			for (int x = 0; x < 3; ++x) {
				subCubes[x][y][z] =
					MAKE_CUBE(CharColorMap.at(data[((z * 3 + y) * 3 + x) * 6 + 0]),
                              CharColorMap.at(data[((z * 3 + y) * 3 + x) * 6 + 1]),
                              CharColorMap.at(data[((z * 3 + y) * 3 + x) * 6 + 2]),
                              CharColorMap.at(data[((z * 3 + y) * 3 + x) * 6 + 3]),
                              CharColorMap.at(data[((z * 3 + y) * 3 + x) * 6 + 4]),
                              CharColorMap.at(data[((z * 3 + y) * 3 + x) * 6 + 5]));
			}
		}
	}
}

std::string Cube::Serialize()
{
	std::string data;
	for (int z = 0; z < 3; ++z) {
		for (int y = 0; y < 3; ++y) {
			for (int x = 0; x < 3; ++x) {
				cube_t subcube = subCubes[x][y][z];
                // Serialize the colors of each face of the subcube
				data += ColorCharMap.at(GET_FRONT(subcube));
				data += ColorCharMap.at(GET_BACK(subcube));
				data += ColorCharMap.at(GET_LEFT(subcube));
				data += ColorCharMap.at(GET_RIGHT(subcube));
				data += ColorCharMap.at(GET_UP(subcube));
				data += ColorCharMap.at(GET_DOWN(subcube));
			}
		}
	}
	return data;
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

bool Cube::CheckL()
{
    // Check if all the cubes in the left face have the same color as the left center cube
	CubeColor centre = GET_LEFT(subCubes[0][1][1]);
	return GET_LEFT(subCubes[0][0][0]) == centre &&
		   GET_LEFT(subCubes[0][0][1]) == centre &&
		   GET_LEFT(subCubes[0][0][2]) == centre &&
		   GET_LEFT(subCubes[0][1][0]) == centre &&
		   GET_LEFT(subCubes[0][1][1]) == centre &&
		   GET_LEFT(subCubes[0][1][2]) == centre &&
		   GET_LEFT(subCubes[0][2][0]) == centre &&
		   GET_LEFT(subCubes[0][2][1]) == centre &&
		   GET_LEFT(subCubes[0][2][2]) == centre;
}

bool Cube::CheckR()
{
    // Check if all the cubes in the right face have the same color as the left center cube
	CubeColor centre = GET_RIGHT(subCubes[2][1][1]);
	return GET_RIGHT(subCubes[2][0][0]) == centre &&
		   GET_RIGHT(subCubes[2][0][1]) == centre &&
		   GET_RIGHT(subCubes[2][0][2]) == centre &&
		   GET_RIGHT(subCubes[2][1][0]) == centre &&
		   GET_RIGHT(subCubes[2][1][1]) == centre &&
		   GET_RIGHT(subCubes[2][1][2]) == centre &&
		   GET_RIGHT(subCubes[2][2][0]) == centre &&
		   GET_RIGHT(subCubes[2][2][1]) == centre &&
		   GET_RIGHT(subCubes[2][2][2]) == centre;
}

bool  Cube::CheckU()
{
    // Check if all the cubes in the up face have the same color as the left center cube
	CubeColor centre = GET_UP(subCubes[1][2][1]);
	return GET_UP(subCubes[0][2][0]) == centre &&
		   GET_UP(subCubes[1][2][0]) == centre &&
		   GET_UP(subCubes[2][2][0]) == centre &&
		   GET_UP(subCubes[0][2][1]) == centre &&
		   GET_UP(subCubes[1][2][1]) == centre &&
		   GET_UP(subCubes[2][2][1]) == centre &&
		   GET_UP(subCubes[0][2][2]) == centre &&
		   GET_UP(subCubes[1][2][2]) == centre &&
		   GET_UP(subCubes[2][2][2]) == centre;
}

bool  Cube::CheckD()
{
    // Check if all the cubes in the down face have the same color as the left center cube
	CubeColor centre = GET_DOWN(subCubes[1][0][1]);
	return GET_DOWN(subCubes[0][0][0]) == centre &&
		   GET_DOWN(subCubes[1][0][0]) == centre &&
		   GET_DOWN(subCubes[2][0][0]) == centre &&
		   GET_DOWN(subCubes[0][0][1]) == centre &&
		   GET_DOWN(subCubes[1][0][1]) == centre &&
		   GET_DOWN(subCubes[2][0][1]) == centre &&
		   GET_DOWN(subCubes[0][0][2]) == centre &&
		   GET_DOWN(subCubes[1][0][2]) == centre &&
		   GET_DOWN(subCubes[2][0][2]) == centre;
}

bool  Cube::CheckF()
{
    // Check if all the cubes in the forward face have the same color as the left center cube
	CubeColor centre = GET_FRONT(subCubes[1][1][2]);
	return GET_FRONT(subCubes[0][0][2]) == centre &&
		   GET_FRONT(subCubes[1][0][2]) == centre &&
		   GET_FRONT(subCubes[2][0][2]) == centre &&
		   GET_FRONT(subCubes[0][1][2]) == centre &&
		   GET_FRONT(subCubes[1][1][2]) == centre &&
		   GET_FRONT(subCubes[2][1][2]) == centre &&
		   GET_FRONT(subCubes[0][2][2]) == centre &&
		   GET_FRONT(subCubes[1][2][2]) == centre &&
		   GET_FRONT(subCubes[2][2][2]) == centre;
}

bool Cube::CheckB()
{
    // Check if all the cubes in the backward face have the same color as the left center cube
	CubeColor centre = GET_BACK(subCubes[1][1][0]);
	return GET_BACK(subCubes[0][0][0]) == centre &&
		   GET_BACK(subCubes[1][0][0]) == centre &&
		   GET_BACK(subCubes[2][0][0]) == centre &&
		   GET_BACK(subCubes[0][1][0]) == centre &&
		   GET_BACK(subCubes[1][1][0]) == centre &&
		   GET_BACK(subCubes[2][1][0]) == centre &&
		   GET_BACK(subCubes[0][2][0]) == centre &&
		   GET_BACK(subCubes[1][2][0]) == centre &&
		   GET_BACK(subCubes[2][2][0]) == centre;
}

bool Cube::Check()
{
    // Check if all faces are in the same color
	return CheckU() && CheckD() && CheckL() && CheckR() && CheckF() && CheckB();
}

// Mapping between characters and cube colors
const std::map<char, CubeColor> Cube::CharColorMap = {
        {'-', COLOR_UNUSED},
        {'W', COLOR_WHITE },
        {'O', COLOR_ORANGE},
        {'B', COLOR_BLUE  },
        {'R', COLOR_RED   },
        {'G', COLOR_GREEN },
        {'Y', COLOR_YELLOW}
};

// Mapping between cube colors and characters
const std::map<CubeColor, char> Cube::ColorCharMap = {
        {COLOR_UNUSED, '-'},
        {COLOR_WHITE , 'W'},
        {COLOR_ORANGE, 'O'},
        {COLOR_BLUE  , 'B'},
        {COLOR_RED   , 'R'},
        {COLOR_GREEN , 'G'},
        {COLOR_YELLOW, 'Y'}
};