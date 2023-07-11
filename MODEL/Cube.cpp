#include "Cube.h"

Cube::Cube()
: m_pSubCubes(std::make_shared<cubes_t>(3, std::vector<std::vector<cube_t>>(3, std::vector<cube_t>(3))))
{
    init();
}

Cube::Cube(const Cube& other)
: m_pSubCubes(std::make_shared<cubes_t>(*(other.m_pSubCubes)))
{
}

Cube::~Cube()
{
}

void Cube::init() {
	// initializing the initial state of the cube，with hexadecimal
    // first layer
	(*m_pSubCubes)[0][0][0] = 0x063002;
    (*m_pSubCubes)[1][0][0] = 0x060002;
    (*m_pSubCubes)[2][0][0] = 0x060402;
    (*m_pSubCubes)[0][0][1] = 0x003002;
    (*m_pSubCubes)[1][0][1] = 0x000002;
    (*m_pSubCubes)[2][0][1] = 0x000402;
    (*m_pSubCubes)[0][0][2] = 0x503002;
    (*m_pSubCubes)[1][0][2] = 0x500002;
    (*m_pSubCubes)[2][0][2] = 0x500402;
    // second layer
    (*m_pSubCubes)[0][1][0] = 0x063000;
    (*m_pSubCubes)[1][1][0] = 0x060000;
    (*m_pSubCubes)[2][1][0] = 0x060400;
    (*m_pSubCubes)[0][1][1] = 0x003000;
    (*m_pSubCubes)[1][1][1] = 0x000000;
    (*m_pSubCubes)[2][1][1] = 0x000400;
    (*m_pSubCubes)[0][1][2] = 0x503000;
    (*m_pSubCubes)[1][1][2] = 0x500000;
    (*m_pSubCubes)[2][1][2] = 0x500400;
    // third layer
    (*m_pSubCubes)[0][2][0] = 0x063010;
    (*m_pSubCubes)[1][2][0] = 0x060010;
    (*m_pSubCubes)[2][2][0] = 0x060410;
    (*m_pSubCubes)[0][2][1] = 0x003010;
    (*m_pSubCubes)[1][2][1] = 0x000010;
    (*m_pSubCubes)[2][2][1] = 0x000410;
    (*m_pSubCubes)[0][2][2] = 0x503010;
    (*m_pSubCubes)[1][2][2] = 0x500010;
    (*m_pSubCubes)[2][2][2] = 0x500410;
}

std::shared_ptr<cubes_t> Cube::getCubeData()
{
    return m_pSubCubes;
}

void Cube::randomCube()
{
    for(int i = 0; i < rand() % 1000 + 1; ++i) {
        CubeRotateMethod method = (CubeRotateMethod)((rand() % 19) + 1);
        doMethod(method);
    }
}

void Cube::deserialize(std::string data)
{
	if (data.length() != FORMAT_LENGTH) {
		throw CubeError("Data length missmatch.");
	}
    // deserializing the cube state from the given data string
	for (int z = 0; z < 3; ++z) {
		for (int y = 0; y < 3; ++y) {
			for (int x = 0; x < 3; ++x) {
				(*m_pSubCubes)[x][y][z] =
					MAKE_CUBE(s_charColorMap.at(data[((z * 3 + y) * 3 + x) * 6 + 0]),
                              s_charColorMap.at(data[((z * 3 + y) * 3 + x) * 6 + 1]),
                              s_charColorMap.at(data[((z * 3 + y) * 3 + x) * 6 + 2]),
                              s_charColorMap.at(data[((z * 3 + y) * 3 + x) * 6 + 3]),
                              s_charColorMap.at(data[((z * 3 + y) * 3 + x) * 6 + 4]),
                              s_charColorMap.at(data[((z * 3 + y) * 3 + x) * 6 + 5]));
			}
		}
	}
}

std::string Cube::serialize()
{
	std::string data;
	for (int z = 0; z < 3; ++z) {
		for (int y = 0; y < 3; ++y) {
			for (int x = 0; x < 3; ++x) {
				cube_t subcube = (*m_pSubCubes)[x][y][z];
                // serialize the colors of each face of the subcube
				data += s_colorCharMap.at(GET_FRONT(subcube));
				data += s_colorCharMap.at(GET_BACK(subcube));
				data += s_colorCharMap.at(GET_LEFT(subcube));
				data += s_colorCharMap.at(GET_RIGHT(subcube));
				data += s_colorCharMap.at(GET_UP(subcube));
				data += s_colorCharMap.at(GET_DOWN(subcube));
			}
		}
	}
	return data;
}

void Cube::doMethod(CubeRotateMethod method)
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
        case ROTATE_WHOLEX: rotateUp(); break;
        case ROTATE_WHOLEY: rotateLeft(); break;
        case ROTATE_WHOLEZ: rotateClockwise(); break;
        case ROTATE_WHOLEXi: rotateDown(); break;
        case ROTATE_WHOLEYi: rotateRight(); break;
        case ROTATE_WHOLEZi: rotateCounterClockwise(); break;
        default: break;
	}
}

// functions for individual cube rotations
void Cube::R()
{
    // perform a rotation on the right face of the cube
	cubes_t oldSubCubes = (*m_pSubCubes);
	(*m_pSubCubes)[2][0][0] = ROTATE_UP(oldSubCubes[2][2][0]);
	(*m_pSubCubes)[2][0][1] = ROTATE_UP(oldSubCubes[2][1][0]);
	(*m_pSubCubes)[2][0][2] = ROTATE_UP(oldSubCubes[2][0][0]);
	(*m_pSubCubes)[2][1][0] = ROTATE_UP(oldSubCubes[2][2][1]);
	(*m_pSubCubes)[2][1][1] = ROTATE_UP(oldSubCubes[2][1][1]);
	(*m_pSubCubes)[2][1][2] = ROTATE_UP(oldSubCubes[2][0][1]);
	(*m_pSubCubes)[2][2][0] = ROTATE_UP(oldSubCubes[2][2][2]);
	(*m_pSubCubes)[2][2][1] = ROTATE_UP(oldSubCubes[2][1][2]);
	(*m_pSubCubes)[2][2][2] = ROTATE_UP(oldSubCubes[2][0][2]);
}

void Cube::Ri()
{
    // perform a counter-clockwise rotation on the right face of the cube
	cubes_t oldSubCubes = (*m_pSubCubes);
	(*m_pSubCubes)[2][0][0] = ROTATE_DOWN(oldSubCubes[2][0][2]);
	(*m_pSubCubes)[2][0][1] = ROTATE_DOWN(oldSubCubes[2][1][2]);
	(*m_pSubCubes)[2][0][2] = ROTATE_DOWN(oldSubCubes[2][2][2]);
	(*m_pSubCubes)[2][1][0] = ROTATE_DOWN(oldSubCubes[2][0][1]);
	(*m_pSubCubes)[2][1][1] = ROTATE_DOWN(oldSubCubes[2][1][1]);
	(*m_pSubCubes)[2][1][2] = ROTATE_DOWN(oldSubCubes[2][2][1]);
	(*m_pSubCubes)[2][2][0] = ROTATE_DOWN(oldSubCubes[2][0][0]);
	(*m_pSubCubes)[2][2][1] = ROTATE_DOWN(oldSubCubes[2][1][0]);
	(*m_pSubCubes)[2][2][2] = ROTATE_DOWN(oldSubCubes[2][2][0]);
}

void Cube::L()
{
    // perform a rotation on the left face of the cube
	cubes_t oldSubCubes = (*m_pSubCubes);
	(*m_pSubCubes)[0][0][0] = ROTATE_DOWN(oldSubCubes[0][0][2]);
	(*m_pSubCubes)[0][0][1] = ROTATE_DOWN(oldSubCubes[0][1][2]);
	(*m_pSubCubes)[0][0][2] = ROTATE_DOWN(oldSubCubes[0][2][2]);
	(*m_pSubCubes)[0][1][0] = ROTATE_DOWN(oldSubCubes[0][0][1]);
	(*m_pSubCubes)[0][1][1] = ROTATE_DOWN(oldSubCubes[0][1][1]);
	(*m_pSubCubes)[0][1][2] = ROTATE_DOWN(oldSubCubes[0][2][1]);
	(*m_pSubCubes)[0][2][0] = ROTATE_DOWN(oldSubCubes[0][0][0]);
	(*m_pSubCubes)[0][2][1] = ROTATE_DOWN(oldSubCubes[0][1][0]);
	(*m_pSubCubes)[0][2][2] = ROTATE_DOWN(oldSubCubes[0][2][0]);
}

void Cube::Li()
{
    // perform a counter-clockwise rotation on the left face of the cube
	cubes_t oldSubCubes = (*m_pSubCubes);
	(*m_pSubCubes)[0][0][0] = ROTATE_UP(oldSubCubes[0][2][0]);
	(*m_pSubCubes)[0][0][1] = ROTATE_UP(oldSubCubes[0][1][0]);
	(*m_pSubCubes)[0][0][2] = ROTATE_UP(oldSubCubes[0][0][0]);
	(*m_pSubCubes)[0][1][0] = ROTATE_UP(oldSubCubes[0][2][1]);
	(*m_pSubCubes)[0][1][1] = ROTATE_UP(oldSubCubes[0][1][1]);
	(*m_pSubCubes)[0][1][2] = ROTATE_UP(oldSubCubes[0][0][1]);
	(*m_pSubCubes)[0][2][0] = ROTATE_UP(oldSubCubes[0][2][2]);
	(*m_pSubCubes)[0][2][1] = ROTATE_UP(oldSubCubes[0][1][2]);
	(*m_pSubCubes)[0][2][2] = ROTATE_UP(oldSubCubes[0][0][2]);
}

void Cube::B()
{
    // perform a rotation on the back face of the cube
	cubes_t oldSubCubes = (*m_pSubCubes);
	(*m_pSubCubes)[0][0][0] = ROTATE_CCLK(oldSubCubes[0][2][0]);
	(*m_pSubCubes)[1][0][0] = ROTATE_CCLK(oldSubCubes[0][1][0]);
	(*m_pSubCubes)[2][0][0] = ROTATE_CCLK(oldSubCubes[0][0][0]);
	(*m_pSubCubes)[0][1][0] = ROTATE_CCLK(oldSubCubes[1][2][0]);
	(*m_pSubCubes)[1][1][0] = ROTATE_CCLK(oldSubCubes[1][1][0]);
	(*m_pSubCubes)[2][1][0] = ROTATE_CCLK(oldSubCubes[1][0][0]);
	(*m_pSubCubes)[0][2][0] = ROTATE_CCLK(oldSubCubes[2][2][0]);
	(*m_pSubCubes)[1][2][0] = ROTATE_CCLK(oldSubCubes[2][1][0]);
	(*m_pSubCubes)[2][2][0] = ROTATE_CCLK(oldSubCubes[2][0][0]);
}

void Cube::Bi()
{
    // perform a counter-clockwise rotation on the back face of the cube
	cubes_t oldSubCubes = (*m_pSubCubes);
	(*m_pSubCubes)[0][0][0] = ROTATE_CLK(oldSubCubes[2][0][0]);
	(*m_pSubCubes)[1][0][0] = ROTATE_CLK(oldSubCubes[2][1][0]);
	(*m_pSubCubes)[2][0][0] = ROTATE_CLK(oldSubCubes[2][2][0]);
	(*m_pSubCubes)[0][1][0] = ROTATE_CLK(oldSubCubes[1][0][0]);
	(*m_pSubCubes)[1][1][0] = ROTATE_CLK(oldSubCubes[1][1][0]);
	(*m_pSubCubes)[2][1][0] = ROTATE_CLK(oldSubCubes[1][2][0]);
	(*m_pSubCubes)[0][2][0] = ROTATE_CLK(oldSubCubes[0][0][0]);
	(*m_pSubCubes)[1][2][0] = ROTATE_CLK(oldSubCubes[0][1][0]);
	(*m_pSubCubes)[2][2][0] = ROTATE_CLK(oldSubCubes[0][2][0]);
}

void Cube::D()
{
    // perform a rotation on the down face of the cube
	cubes_t oldSubCubes = (*m_pSubCubes);
	(*m_pSubCubes)[0][0][0] = ROTATE_RIGHT(oldSubCubes[2][0][0]);
	(*m_pSubCubes)[1][0][0] = ROTATE_RIGHT(oldSubCubes[2][0][1]);
	(*m_pSubCubes)[2][0][0] = ROTATE_RIGHT(oldSubCubes[2][0][2]);
	(*m_pSubCubes)[0][0][1] = ROTATE_RIGHT(oldSubCubes[1][0][0]);
	(*m_pSubCubes)[1][0][1] = ROTATE_RIGHT(oldSubCubes[1][0][1]);
	(*m_pSubCubes)[2][0][1] = ROTATE_RIGHT(oldSubCubes[1][0][2]);
	(*m_pSubCubes)[0][0][2] = ROTATE_RIGHT(oldSubCubes[0][0][0]);
	(*m_pSubCubes)[1][0][2] = ROTATE_RIGHT(oldSubCubes[0][0][1]);
	(*m_pSubCubes)[2][0][2] = ROTATE_RIGHT(oldSubCubes[0][0][2]);
}

void Cube::Di()
{
    // perform a counter-clockwise rotation on the down face of the cube
	cubes_t oldSubCubes = (*m_pSubCubes);
	(*m_pSubCubes)[0][0][0] = ROTATE_LEFT(oldSubCubes[0][0][2]);
	(*m_pSubCubes)[1][0][0] = ROTATE_LEFT(oldSubCubes[0][0][1]);
	(*m_pSubCubes)[2][0][0] = ROTATE_LEFT(oldSubCubes[0][0][0]);
	(*m_pSubCubes)[0][0][1] = ROTATE_LEFT(oldSubCubes[1][0][2]);
	(*m_pSubCubes)[1][0][1] = ROTATE_LEFT(oldSubCubes[1][0][1]);
	(*m_pSubCubes)[2][0][1] = ROTATE_LEFT(oldSubCubes[1][0][0]);
	(*m_pSubCubes)[0][0][2] = ROTATE_LEFT(oldSubCubes[2][0][2]);
	(*m_pSubCubes)[1][0][2] = ROTATE_LEFT(oldSubCubes[2][0][1]);
	(*m_pSubCubes)[2][0][2] = ROTATE_LEFT(oldSubCubes[2][0][0]);
}

void Cube::F()
{
    // perform a rotation on the front face of the cube
	cubes_t oldSubCubes = (*m_pSubCubes);
	(*m_pSubCubes)[0][0][2] = ROTATE_CLK(oldSubCubes[2][0][2]);
	(*m_pSubCubes)[1][0][2] = ROTATE_CLK(oldSubCubes[2][1][2]);
	(*m_pSubCubes)[2][0][2] = ROTATE_CLK(oldSubCubes[2][2][2]);
	(*m_pSubCubes)[0][1][2] = ROTATE_CLK(oldSubCubes[1][0][2]);
	(*m_pSubCubes)[1][1][2] = ROTATE_CLK(oldSubCubes[1][1][2]);
	(*m_pSubCubes)[2][1][2] = ROTATE_CLK(oldSubCubes[1][2][2]);
	(*m_pSubCubes)[0][2][2] = ROTATE_CLK(oldSubCubes[0][0][2]);
	(*m_pSubCubes)[1][2][2] = ROTATE_CLK(oldSubCubes[0][1][2]);
	(*m_pSubCubes)[2][2][2] = ROTATE_CLK(oldSubCubes[0][2][2]);
}

void Cube::Fi()
{
    // perform a counter-clockwise rotation on the front face of the cube
	cubes_t oldSubCubes = (*m_pSubCubes);
	(*m_pSubCubes)[0][0][2] = ROTATE_CCLK(oldSubCubes[0][2][2]);
	(*m_pSubCubes)[1][0][2] = ROTATE_CCLK(oldSubCubes[0][1][2]);
	(*m_pSubCubes)[2][0][2] = ROTATE_CCLK(oldSubCubes[0][0][2]);
	(*m_pSubCubes)[0][1][2] = ROTATE_CCLK(oldSubCubes[1][2][2]);
	(*m_pSubCubes)[1][1][2] = ROTATE_CCLK(oldSubCubes[1][1][2]);
	(*m_pSubCubes)[2][1][2] = ROTATE_CCLK(oldSubCubes[1][0][2]);
	(*m_pSubCubes)[0][2][2] = ROTATE_CCLK(oldSubCubes[2][2][2]);
	(*m_pSubCubes)[1][2][2] = ROTATE_CCLK(oldSubCubes[2][1][2]);
	(*m_pSubCubes)[2][2][2] = ROTATE_CCLK(oldSubCubes[2][0][2]);
}

void Cube::U()
{
    // perform a rotation on the up face of the cube
	cubes_t oldSubCubes = (*m_pSubCubes);
	(*m_pSubCubes)[0][2][0] = ROTATE_LEFT(oldSubCubes[0][2][2]);
	(*m_pSubCubes)[1][2][0] = ROTATE_LEFT(oldSubCubes[0][2][1]);
	(*m_pSubCubes)[2][2][0] = ROTATE_LEFT(oldSubCubes[0][2][0]);
	(*m_pSubCubes)[0][2][1] = ROTATE_LEFT(oldSubCubes[1][2][2]);
	(*m_pSubCubes)[1][2][1] = ROTATE_LEFT(oldSubCubes[1][2][1]);
	(*m_pSubCubes)[2][2][1] = ROTATE_LEFT(oldSubCubes[1][2][0]);
	(*m_pSubCubes)[0][2][2] = ROTATE_LEFT(oldSubCubes[2][2][2]);
	(*m_pSubCubes)[1][2][2] = ROTATE_LEFT(oldSubCubes[2][2][1]);
	(*m_pSubCubes)[2][2][2] = ROTATE_LEFT(oldSubCubes[2][2][0]);
}

void Cube::Ui()
{
    // perform a counter-clockwise rotation on the up face of the cube
	cubes_t oldSubCubes = (*m_pSubCubes);
	(*m_pSubCubes)[0][2][0] = ROTATE_RIGHT(oldSubCubes[2][2][0]);
	(*m_pSubCubes)[1][2][0] = ROTATE_RIGHT(oldSubCubes[2][2][1]);
	(*m_pSubCubes)[2][2][0] = ROTATE_RIGHT(oldSubCubes[2][2][2]);
	(*m_pSubCubes)[0][2][1] = ROTATE_RIGHT(oldSubCubes[1][2][0]);
	(*m_pSubCubes)[1][2][1] = ROTATE_RIGHT(oldSubCubes[1][2][1]);
	(*m_pSubCubes)[2][2][1] = ROTATE_RIGHT(oldSubCubes[1][2][2]);
	(*m_pSubCubes)[0][2][2] = ROTATE_RIGHT(oldSubCubes[0][2][0]);
	(*m_pSubCubes)[1][2][2] = ROTATE_RIGHT(oldSubCubes[0][2][1]);
	(*m_pSubCubes)[2][2][2] = ROTATE_RIGHT(oldSubCubes[0][2][2]);
}

void Cube::rotateLeft()
{
	U(); // rotate the Up face clockwise
	cubes_t oldSubCubes = (*m_pSubCubes);
	(*m_pSubCubes)[0][1][0] = ROTATE_LEFT(oldSubCubes[0][1][2]);
	(*m_pSubCubes)[1][1][0] = ROTATE_LEFT(oldSubCubes[0][1][1]);
	(*m_pSubCubes)[2][1][0] = ROTATE_LEFT(oldSubCubes[0][1][0]);
	(*m_pSubCubes)[0][1][1] = ROTATE_LEFT(oldSubCubes[1][1][2]);
	(*m_pSubCubes)[1][1][1] = ROTATE_LEFT(oldSubCubes[1][1][1]);
	(*m_pSubCubes)[2][1][1] = ROTATE_LEFT(oldSubCubes[1][1][0]);
	(*m_pSubCubes)[0][1][2] = ROTATE_LEFT(oldSubCubes[2][1][2]);
	(*m_pSubCubes)[1][1][2] = ROTATE_LEFT(oldSubCubes[2][1][1]);
	(*m_pSubCubes)[2][1][2] = ROTATE_LEFT(oldSubCubes[2][1][0]);
	Di(); // rotate the Down face counter-clockwise
}

void Cube::rotateRight()
{
	Ui(); // rotate the Up face counter-clockwise
	cubes_t oldSubCubes = (*m_pSubCubes);
	(*m_pSubCubes)[0][1][0] = ROTATE_RIGHT(oldSubCubes[2][1][0]);
	(*m_pSubCubes)[1][1][0] = ROTATE_RIGHT(oldSubCubes[2][1][1]);
	(*m_pSubCubes)[2][1][0] = ROTATE_RIGHT(oldSubCubes[2][1][2]);
	(*m_pSubCubes)[0][1][1] = ROTATE_RIGHT(oldSubCubes[1][1][0]);
	(*m_pSubCubes)[1][1][1] = ROTATE_RIGHT(oldSubCubes[1][1][1]);
	(*m_pSubCubes)[2][1][1] = ROTATE_RIGHT(oldSubCubes[1][1][2]);
	(*m_pSubCubes)[0][1][2] = ROTATE_RIGHT(oldSubCubes[0][1][0]);
	(*m_pSubCubes)[1][1][2] = ROTATE_RIGHT(oldSubCubes[0][1][1]);
	(*m_pSubCubes)[2][1][2] = ROTATE_RIGHT(oldSubCubes[0][1][2]);
	D(); // rotate the Down face clockwise

}

void Cube::rotateUp()
{
	Li(); // Rotate the Left face counter-clockwise
	cubes_t oldSubCubes = (*m_pSubCubes);
	(*m_pSubCubes)[1][0][0] = ROTATE_UP(oldSubCubes[1][2][0]);
	(*m_pSubCubes)[1][0][1] = ROTATE_UP(oldSubCubes[1][1][0]);
	(*m_pSubCubes)[1][0][2] = ROTATE_UP(oldSubCubes[1][0][0]);
	(*m_pSubCubes)[1][1][0] = ROTATE_UP(oldSubCubes[1][2][1]);
	(*m_pSubCubes)[1][1][1] = ROTATE_UP(oldSubCubes[1][1][1]);
	(*m_pSubCubes)[1][1][2] = ROTATE_UP(oldSubCubes[1][0][1]);
	(*m_pSubCubes)[1][2][0] = ROTATE_UP(oldSubCubes[1][2][2]);
	(*m_pSubCubes)[1][2][1] = ROTATE_UP(oldSubCubes[1][1][2]);
	(*m_pSubCubes)[1][2][2] = ROTATE_UP(oldSubCubes[1][0][2]);
	R(); // rotate the Right face clockwise
}

void Cube::rotateDown()
{
	L(); // rotate the Left face clockwise
	cubes_t oldSubCubes = (*m_pSubCubes);
	(*m_pSubCubes)[1][0][0] = ROTATE_DOWN(oldSubCubes[1][0][2]);
	(*m_pSubCubes)[1][0][1] = ROTATE_DOWN(oldSubCubes[1][1][2]);
	(*m_pSubCubes)[1][0][2] = ROTATE_DOWN(oldSubCubes[1][2][2]);
	(*m_pSubCubes)[1][1][0] = ROTATE_DOWN(oldSubCubes[1][0][1]);
	(*m_pSubCubes)[1][1][1] = ROTATE_DOWN(oldSubCubes[1][1][1]);
	(*m_pSubCubes)[1][1][2] = ROTATE_DOWN(oldSubCubes[1][2][1]);
	(*m_pSubCubes)[1][2][0] = ROTATE_DOWN(oldSubCubes[1][0][0]);
	(*m_pSubCubes)[1][2][1] = ROTATE_DOWN(oldSubCubes[1][1][0]);
	(*m_pSubCubes)[1][2][2] = ROTATE_DOWN(oldSubCubes[1][2][0]);
	Ri(); // rotate the Right face counter-clockwise
}

void Cube::rotateClockwise()
{
	F(); // rotate the Front face clockwise
	cubes_t oldSubCubes = (*m_pSubCubes);
	(*m_pSubCubes)[0][0][1] = ROTATE_CLK(oldSubCubes[2][0][1]);
	(*m_pSubCubes)[1][0][1] = ROTATE_CLK(oldSubCubes[2][1][1]);
	(*m_pSubCubes)[2][0][1] = ROTATE_CLK(oldSubCubes[2][2][1]);
	(*m_pSubCubes)[0][1][1] = ROTATE_CLK(oldSubCubes[1][0][1]);
	(*m_pSubCubes)[1][1][1] = ROTATE_CLK(oldSubCubes[1][1][1]);
	(*m_pSubCubes)[2][1][1] = ROTATE_CLK(oldSubCubes[1][2][1]);
	(*m_pSubCubes)[0][2][1] = ROTATE_CLK(oldSubCubes[0][0][1]);
	(*m_pSubCubes)[1][2][1] = ROTATE_CLK(oldSubCubes[0][1][1]);
	(*m_pSubCubes)[2][2][1] = ROTATE_CLK(oldSubCubes[0][2][1]);
	Bi(); // rotate the Back face counter-clockwise
}

void Cube::rotateCounterClockwise()
{
	Fi(); // rotate the Front face counter-clockwise
	cubes_t oldSubCubes = (*m_pSubCubes);
	(*m_pSubCubes)[0][0][1] = ROTATE_CCLK(oldSubCubes[0][2][1]);
	(*m_pSubCubes)[1][0][1] = ROTATE_CCLK(oldSubCubes[0][1][1]);
	(*m_pSubCubes)[2][0][1] = ROTATE_CCLK(oldSubCubes[0][0][1]);
	(*m_pSubCubes)[0][1][1] = ROTATE_CCLK(oldSubCubes[1][2][1]);
	(*m_pSubCubes)[1][1][1] = ROTATE_CCLK(oldSubCubes[1][1][1]);
	(*m_pSubCubes)[2][1][1] = ROTATE_CCLK(oldSubCubes[1][0][1]);
	(*m_pSubCubes)[0][2][1] = ROTATE_CCLK(oldSubCubes[2][2][1]);
	(*m_pSubCubes)[1][2][1] = ROTATE_CCLK(oldSubCubes[2][1][1]);
	(*m_pSubCubes)[2][2][1] = ROTATE_CCLK(oldSubCubes[2][0][1]);
	B(); // rotate the Back face clockwise
}

bool Cube::checkL()
{
    // check if all the cubes in the left face have the same color as the left center cube
	CubeColor centre = GET_LEFT((*m_pSubCubes)[0][1][1]);
	return GET_LEFT((*m_pSubCubes)[0][0][0]) == centre &&
		   GET_LEFT((*m_pSubCubes)[0][0][1]) == centre &&
		   GET_LEFT((*m_pSubCubes)[0][0][2]) == centre &&
		   GET_LEFT((*m_pSubCubes)[0][1][0]) == centre &&
		   GET_LEFT((*m_pSubCubes)[0][1][1]) == centre &&
		   GET_LEFT((*m_pSubCubes)[0][1][2]) == centre &&
		   GET_LEFT((*m_pSubCubes)[0][2][0]) == centre &&
		   GET_LEFT((*m_pSubCubes)[0][2][1]) == centre &&
		   GET_LEFT((*m_pSubCubes)[0][2][2]) == centre;
}

bool Cube::checkR()
{
    // check if all the cubes in the right face have the same color as the left center cube
	CubeColor centre = GET_RIGHT((*m_pSubCubes)[2][1][1]);
	return GET_RIGHT((*m_pSubCubes)[2][0][0]) == centre &&
		   GET_RIGHT((*m_pSubCubes)[2][0][1]) == centre &&
		   GET_RIGHT((*m_pSubCubes)[2][0][2]) == centre &&
		   GET_RIGHT((*m_pSubCubes)[2][1][0]) == centre &&
		   GET_RIGHT((*m_pSubCubes)[2][1][1]) == centre &&
		   GET_RIGHT((*m_pSubCubes)[2][1][2]) == centre &&
		   GET_RIGHT((*m_pSubCubes)[2][2][0]) == centre &&
		   GET_RIGHT((*m_pSubCubes)[2][2][1]) == centre &&
		   GET_RIGHT((*m_pSubCubes)[2][2][2]) == centre;
}

bool  Cube::checkU()
{
    // check if all the cubes in the up face have the same color as the left center cube
	CubeColor centre = GET_UP((*m_pSubCubes)[1][2][1]);
	return GET_UP((*m_pSubCubes)[0][2][0]) == centre &&
		   GET_UP((*m_pSubCubes)[1][2][0]) == centre &&
		   GET_UP((*m_pSubCubes)[2][2][0]) == centre &&
		   GET_UP((*m_pSubCubes)[0][2][1]) == centre &&
		   GET_UP((*m_pSubCubes)[1][2][1]) == centre &&
		   GET_UP((*m_pSubCubes)[2][2][1]) == centre &&
		   GET_UP((*m_pSubCubes)[0][2][2]) == centre &&
		   GET_UP((*m_pSubCubes)[1][2][2]) == centre &&
		   GET_UP((*m_pSubCubes)[2][2][2]) == centre;
}

bool  Cube::checkD()
{
    // check if all the cubes in the down face have the same color as the left center cube
	CubeColor centre = GET_DOWN((*m_pSubCubes)[1][0][1]);
	return GET_DOWN((*m_pSubCubes)[0][0][0]) == centre &&
		   GET_DOWN((*m_pSubCubes)[1][0][0]) == centre &&
		   GET_DOWN((*m_pSubCubes)[2][0][0]) == centre &&
		   GET_DOWN((*m_pSubCubes)[0][0][1]) == centre &&
		   GET_DOWN((*m_pSubCubes)[1][0][1]) == centre &&
		   GET_DOWN((*m_pSubCubes)[2][0][1]) == centre &&
		   GET_DOWN((*m_pSubCubes)[0][0][2]) == centre &&
		   GET_DOWN((*m_pSubCubes)[1][0][2]) == centre &&
		   GET_DOWN((*m_pSubCubes)[2][0][2]) == centre;
}

bool  Cube::checkF()
{
    // check if all the cubes in the forward face have the same color as the left center cube
	CubeColor centre = GET_FRONT((*m_pSubCubes)[1][1][2]);
	return GET_FRONT((*m_pSubCubes)[0][0][2]) == centre &&
		   GET_FRONT((*m_pSubCubes)[1][0][2]) == centre &&
		   GET_FRONT((*m_pSubCubes)[2][0][2]) == centre &&
		   GET_FRONT((*m_pSubCubes)[0][1][2]) == centre &&
		   GET_FRONT((*m_pSubCubes)[1][1][2]) == centre &&
		   GET_FRONT((*m_pSubCubes)[2][1][2]) == centre &&
		   GET_FRONT((*m_pSubCubes)[0][2][2]) == centre &&
		   GET_FRONT((*m_pSubCubes)[1][2][2]) == centre &&
		   GET_FRONT((*m_pSubCubes)[2][2][2]) == centre;
}

bool Cube::checkB()
{
    // Check if all the cubes in the backward face have the same color as the left center cube
	CubeColor centre = GET_BACK((*m_pSubCubes)[1][1][0]);
	return GET_BACK((*m_pSubCubes)[0][0][0]) == centre &&
		   GET_BACK((*m_pSubCubes)[1][0][0]) == centre &&
		   GET_BACK((*m_pSubCubes)[2][0][0]) == centre &&
		   GET_BACK((*m_pSubCubes)[0][1][0]) == centre &&
		   GET_BACK((*m_pSubCubes)[1][1][0]) == centre &&
		   GET_BACK((*m_pSubCubes)[2][1][0]) == centre &&
		   GET_BACK((*m_pSubCubes)[0][2][0]) == centre &&
		   GET_BACK((*m_pSubCubes)[1][2][0]) == centre &&
		   GET_BACK((*m_pSubCubes)[2][2][0]) == centre;
}

bool Cube::check()
{
    // Check if all faces are in the same color
	return checkU() && checkD() && checkL() && checkR() && checkF() && checkB();
}

// mapping between characters and cube colors
const std::map<char, CubeColor> Cube::s_charColorMap = {
        {'-', COLOR_UNUSED},
        {'W', COLOR_WHITE },
        {'O', COLOR_ORANGE},
        {'B', COLOR_BLUE  },
        {'R', COLOR_RED   },
        {'G', COLOR_GREEN },
        {'Y', COLOR_YELLOW}
};

// mapping between cube colors and characters
const std::map<CubeColor, char> Cube::s_colorCharMap = {
        {COLOR_UNUSED, '-'},
        {COLOR_WHITE , 'W'},
        {COLOR_ORANGE, 'O'},
        {COLOR_BLUE  , 'B'},
        {COLOR_RED   , 'R'},
        {COLOR_GREEN , 'G'},
        {COLOR_YELLOW, 'Y'}
};