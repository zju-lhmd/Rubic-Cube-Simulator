#include "CubeModel.h"

CubeModel::CubeModel()
{
    // initialize the cube size (3 * 3 * 3)
	m_subCubes.resize(3);
	for(int i = 0;i < 3;++i) {
		m_subCubes[i].resize(3);
		for(int j = 0;j < 3;++j) {
			m_subCubes[i][j].resize(3);
		}
	}
	// initialize the cube state
    init();
}

CubeModel::CubeModel(const CubeModel &other)
    : m_subCubes(other.m_subCubes)
{
}

CubeModel::~CubeModel()
{
}

// initialize cube state
void CubeModel::init() {
    // first layer
    m_subCubes[0][0][0] = 0x063002;
    m_subCubes[1][0][0] = 0x060002;
    m_subCubes[2][0][0] = 0x060402;
    m_subCubes[0][0][1] = 0x003002;
    m_subCubes[1][0][1] = 0x000002;
    m_subCubes[2][0][1] = 0x000402;
    m_subCubes[0][0][2] = 0x503002;
    m_subCubes[1][0][2] = 0x500002;
    m_subCubes[2][0][2] = 0x500402;
    // second layer
    m_subCubes[0][1][0] = 0x063000;
    m_subCubes[1][1][0] = 0x060000;
    m_subCubes[2][1][0] = 0x060400;
    m_subCubes[0][1][1] = 0x003000;
    m_subCubes[1][1][1] = 0x000000;
    m_subCubes[2][1][1] = 0x000400;
    m_subCubes[0][1][2] = 0x503000;
    m_subCubes[1][1][2] = 0x500000;
    m_subCubes[2][1][2] = 0x500400;
    // third layer
    m_subCubes[0][2][0] = 0x063010;
    m_subCubes[1][2][0] = 0x060010;
    m_subCubes[2][2][0] = 0x060410;
    m_subCubes[0][2][1] = 0x003010;
    m_subCubes[1][2][1] = 0x000010;
    m_subCubes[2][2][1] = 0x000410;
    m_subCubes[0][2][2] = 0x503010;
    m_subCubes[1][2][2] = 0x500010;
    m_subCubes[2][2][2] = 0x500410;
}

cubes_t CubeModel::getCubes()
{
    return m_subCubes;
}

void CubeModel::randomCube()
{
    return ;
}

void CubeModel::deserialize(std::string data)
{
	return ;
}

std::string CubeModel::serialize()
{
	return ;
}

void CubeModel::doMethod(CubeRotateMethod method)
{
    // perform a cube rotation based on the given method
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

// single cube rotation
void CubeModel::R()
{
    // perform a rotation on the right face of the cube
	cubes_t oldSubCubes(m_subCubes);
	m_subCubes[2][0][0] = ROTATE_UP(oldSubCubes[2][2][0]);
	m_subCubes[2][0][1] = ROTATE_UP(oldSubCubes[2][1][0]);
	m_subCubes[2][0][2] = ROTATE_UP(oldSubCubes[2][0][0]);
	m_subCubes[2][1][0] = ROTATE_UP(oldSubCubes[2][2][1]);
	m_subCubes[2][1][1] = ROTATE_UP(oldSubCubes[2][1][1]);
	m_subCubes[2][1][2] = ROTATE_UP(oldSubCubes[2][0][1]);
	m_subCubes[2][2][0] = ROTATE_UP(oldSubCubes[2][2][2]);
	m_subCubes[2][2][1] = ROTATE_UP(oldSubCubes[2][1][2]);
	m_subCubes[2][2][2] = ROTATE_UP(oldSubCubes[2][0][2]);
}

void CubeModel::Ri()
{
    // perform a counter-clockwise rotation on the right face of the cube
	cubes_t oldSubCubes(m_subCubes);
	m_subCubes[2][0][0] = ROTATE_DOWN(oldSubCubes[2][0][2]);
	m_subCubes[2][0][1] = ROTATE_DOWN(oldSubCubes[2][1][2]);
	m_subCubes[2][0][2] = ROTATE_DOWN(oldSubCubes[2][2][2]);
	m_subCubes[2][1][0] = ROTATE_DOWN(oldSubCubes[2][0][1]);
	m_subCubes[2][1][1] = ROTATE_DOWN(oldSubCubes[2][1][1]);
	m_subCubes[2][1][2] = ROTATE_DOWN(oldSubCubes[2][2][1]);
	m_subCubes[2][2][0] = ROTATE_DOWN(oldSubCubes[2][0][0]);
	m_subCubes[2][2][1] = ROTATE_DOWN(oldSubCubes[2][1][0]);
	m_subCubes[2][2][2] = ROTATE_DOWN(oldSubCubes[2][2][0]);
}

void CubeModel::L()
{
    // perform a rotation on the left face of the cube
	cubes_t oldSubCubes(m_subCubes);
	m_subCubes[0][0][0] = ROTATE_DOWN(oldSubCubes[0][0][2]);
	m_subCubes[0][0][1] = ROTATE_DOWN(oldSubCubes[0][1][2]);
	m_subCubes[0][0][2] = ROTATE_DOWN(oldSubCubes[0][2][2]);
	m_subCubes[0][1][0] = ROTATE_DOWN(oldSubCubes[0][0][1]);
	m_subCubes[0][1][1] = ROTATE_DOWN(oldSubCubes[0][1][1]);
	m_subCubes[0][1][2] = ROTATE_DOWN(oldSubCubes[0][2][1]);
	m_subCubes[0][2][0] = ROTATE_DOWN(oldSubCubes[0][0][0]);
	m_subCubes[0][2][1] = ROTATE_DOWN(oldSubCubes[0][1][0]);
	m_subCubes[0][2][2] = ROTATE_DOWN(oldSubCubes[0][2][0]);
}

void CubeModel::Li()
{
    // perform a counter-clockwise rotation on the left face of the cube
	cubes_t oldSubCubes(m_subCubes);
	m_subCubes[0][0][0] = ROTATE_UP(oldSubCubes[0][2][0]);
	m_subCubes[0][0][1] = ROTATE_UP(oldSubCubes[0][1][0]);
	m_subCubes[0][0][2] = ROTATE_UP(oldSubCubes[0][0][0]);
	m_subCubes[0][1][0] = ROTATE_UP(oldSubCubes[0][2][1]);
	m_subCubes[0][1][1] = ROTATE_UP(oldSubCubes[0][1][1]);
	m_subCubes[0][1][2] = ROTATE_UP(oldSubCubes[0][0][1]);
	m_subCubes[0][2][0] = ROTATE_UP(oldSubCubes[0][2][2]);
	m_subCubes[0][2][1] = ROTATE_UP(oldSubCubes[0][1][2]);
	m_subCubes[0][2][2] = ROTATE_UP(oldSubCubes[0][0][2]);
}

void CubeModel::B()
{
    // perform a rotation on the back face of the cube
	cubes_t oldSubCubes(m_subCubes);
	m_subCubes[0][0][0] = ROTATE_CCLK(oldSubCubes[0][2][0]);
	m_subCubes[1][0][0] = ROTATE_CCLK(oldSubCubes[0][1][0]);
	m_subCubes[2][0][0] = ROTATE_CCLK(oldSubCubes[0][0][0]);
	m_subCubes[0][1][0] = ROTATE_CCLK(oldSubCubes[1][2][0]);
	m_subCubes[1][1][0] = ROTATE_CCLK(oldSubCubes[1][1][0]);
	m_subCubes[2][1][0] = ROTATE_CCLK(oldSubCubes[1][0][0]);
	m_subCubes[0][2][0] = ROTATE_CCLK(oldSubCubes[2][2][0]);
	m_subCubes[1][2][0] = ROTATE_CCLK(oldSubCubes[2][1][0]);
	m_subCubes[2][2][0] = ROTATE_CCLK(oldSubCubes[2][0][0]);
}

void CubeModel::Bi()
{
    // perform a counter-clockwise rotation on the back face of the cube
	cubes_t oldSubCubes(m_subCubes);
	m_subCubes[0][0][0] = ROTATE_CLK(oldSubCubes[2][0][0]);
	m_subCubes[1][0][0] = ROTATE_CLK(oldSubCubes[2][1][0]);
	m_subCubes[2][0][0] = ROTATE_CLK(oldSubCubes[2][2][0]);
	m_subCubes[0][1][0] = ROTATE_CLK(oldSubCubes[1][0][0]);
	m_subCubes[1][1][0] = ROTATE_CLK(oldSubCubes[1][1][0]);
	m_subCubes[2][1][0] = ROTATE_CLK(oldSubCubes[1][2][0]);
	m_subCubes[0][2][0] = ROTATE_CLK(oldSubCubes[0][0][0]);
	m_subCubes[1][2][0] = ROTATE_CLK(oldSubCubes[0][1][0]);
	m_subCubes[2][2][0] = ROTATE_CLK(oldSubCubes[0][2][0]);
}

void CubeModel::D()
{
    // perform a rotation on the down face of the cube
	cubes_t oldSubCubes(m_subCubes);
	m_subCubes[0][0][0] = ROTATE_RIGHT(oldSubCubes[2][0][0]);
	m_subCubes[1][0][0] = ROTATE_RIGHT(oldSubCubes[2][0][1]);
	m_subCubes[2][0][0] = ROTATE_RIGHT(oldSubCubes[2][0][2]);
	m_subCubes[0][0][1] = ROTATE_RIGHT(oldSubCubes[1][0][0]);
	m_subCubes[1][0][1] = ROTATE_RIGHT(oldSubCubes[1][0][1]);
	m_subCubes[2][0][1] = ROTATE_RIGHT(oldSubCubes[1][0][2]);
	m_subCubes[0][0][2] = ROTATE_RIGHT(oldSubCubes[0][0][0]);
	m_subCubes[1][0][2] = ROTATE_RIGHT(oldSubCubes[0][0][1]);
	m_subCubes[2][0][2] = ROTATE_RIGHT(oldSubCubes[0][0][2]);
}

void CubeModel::Di()
{
    // perform a counter-clockwise rotation on the down face of the cube
	cubes_t oldSubCubes(m_subCubes);
	m_subCubes[0][0][0] = ROTATE_LEFT(oldSubCubes[0][0][2]);
	m_subCubes[1][0][0] = ROTATE_LEFT(oldSubCubes[0][0][1]);
	m_subCubes[2][0][0] = ROTATE_LEFT(oldSubCubes[0][0][0]);
	m_subCubes[0][0][1] = ROTATE_LEFT(oldSubCubes[1][0][2]);
	m_subCubes[1][0][1] = ROTATE_LEFT(oldSubCubes[1][0][1]);
	m_subCubes[2][0][1] = ROTATE_LEFT(oldSubCubes[1][0][0]);
	m_subCubes[0][0][2] = ROTATE_LEFT(oldSubCubes[2][0][2]);
	m_subCubes[1][0][2] = ROTATE_LEFT(oldSubCubes[2][0][1]);
	m_subCubes[2][0][2] = ROTATE_LEFT(oldSubCubes[2][0][0]);
}

void CubeModel::F()
{
    // perform a rotation on the front face of the cube
	cubes_t oldSubCubes(m_subCubes);
	m_subCubes[0][0][2] = ROTATE_CLK(oldSubCubes[2][0][2]);
	m_subCubes[1][0][2] = ROTATE_CLK(oldSubCubes[2][1][2]);
	m_subCubes[2][0][2] = ROTATE_CLK(oldSubCubes[2][2][2]);
	m_subCubes[0][1][2] = ROTATE_CLK(oldSubCubes[1][0][2]);
	m_subCubes[1][1][2] = ROTATE_CLK(oldSubCubes[1][1][2]);
	m_subCubes[2][1][2] = ROTATE_CLK(oldSubCubes[1][2][2]);
	m_subCubes[0][2][2] = ROTATE_CLK(oldSubCubes[0][0][2]);
	m_subCubes[1][2][2] = ROTATE_CLK(oldSubCubes[0][1][2]);
	m_subCubes[2][2][2] = ROTATE_CLK(oldSubCubes[0][2][2]);
}

void CubeModel::Fi()
{
    // perform a counter-clockwise rotation on the front face of the cube
	cubes_t oldSubCubes(m_subCubes);
	m_subCubes[0][0][2] = ROTATE_CCLK(oldSubCubes[0][2][2]);
	m_subCubes[1][0][2] = ROTATE_CCLK(oldSubCubes[0][1][2]);
	m_subCubes[2][0][2] = ROTATE_CCLK(oldSubCubes[0][0][2]);
	m_subCubes[0][1][2] = ROTATE_CCLK(oldSubCubes[1][2][2]);
	m_subCubes[1][1][2] = ROTATE_CCLK(oldSubCubes[1][1][2]);
	m_subCubes[2][1][2] = ROTATE_CCLK(oldSubCubes[1][0][2]);
	m_subCubes[0][2][2] = ROTATE_CCLK(oldSubCubes[2][2][2]);
	m_subCubes[1][2][2] = ROTATE_CCLK(oldSubCubes[2][1][2]);
	m_subCubes[2][2][2] = ROTATE_CCLK(oldSubCubes[2][0][2]);
}

void CubeModel::U()
{
    // perform a rotation on the up face of the cube
	cubes_t oldSubCubes(m_subCubes);
	m_subCubes[0][2][0] = ROTATE_LEFT(oldSubCubes[0][2][2]);
	m_subCubes[1][2][0] = ROTATE_LEFT(oldSubCubes[0][2][1]);
	m_subCubes[2][2][0] = ROTATE_LEFT(oldSubCubes[0][2][0]);
	m_subCubes[0][2][1] = ROTATE_LEFT(oldSubCubes[1][2][2]);
	m_subCubes[1][2][1] = ROTATE_LEFT(oldSubCubes[1][2][1]);
	m_subCubes[2][2][1] = ROTATE_LEFT(oldSubCubes[1][2][0]);
	m_subCubes[0][2][2] = ROTATE_LEFT(oldSubCubes[2][2][2]);
	m_subCubes[1][2][2] = ROTATE_LEFT(oldSubCubes[2][2][1]);
	m_subCubes[2][2][2] = ROTATE_LEFT(oldSubCubes[2][2][0]);
}

void CubeModel::Ui()
{
    // perform a counter-clockwise rotation on the up face of the cube
	cubes_t oldSubCubes(m_subCubes);
	m_subCubes[0][2][0] = ROTATE_RIGHT(oldSubCubes[2][2][0]);
	m_subCubes[1][2][0] = ROTATE_RIGHT(oldSubCubes[2][2][1]);
	m_subCubes[2][2][0] = ROTATE_RIGHT(oldSubCubes[2][2][2]);
	m_subCubes[0][2][1] = ROTATE_RIGHT(oldSubCubes[1][2][0]);
	m_subCubes[1][2][1] = ROTATE_RIGHT(oldSubCubes[1][2][1]);
	m_subCubes[2][2][1] = ROTATE_RIGHT(oldSubCubes[1][2][2]);
	m_subCubes[0][2][2] = ROTATE_RIGHT(oldSubCubes[0][2][0]);
	m_subCubes[1][2][2] = ROTATE_RIGHT(oldSubCubes[0][2][1]);
	m_subCubes[2][2][2] = ROTATE_RIGHT(oldSubCubes[0][2][2]);
}

void CubeModel::rotateLeft()
{
	U(); // rotate the Up face clockwise
	cubes_t oldSubCubes(m_subCubes);
    // rotate the left face clockwise
	m_subCubes[0][1][0] = ROTATE_LEFT(oldSubCubes[0][1][2]);
	m_subCubes[1][1][0] = ROTATE_LEFT(oldSubCubes[0][1][1]);
	m_subCubes[2][1][0] = ROTATE_LEFT(oldSubCubes[0][1][0]);
	m_subCubes[0][1][1] = ROTATE_LEFT(oldSubCubes[1][1][2]);
	m_subCubes[1][1][1] = ROTATE_LEFT(oldSubCubes[1][1][1]);
	m_subCubes[2][1][1] = ROTATE_LEFT(oldSubCubes[1][1][0]);
	m_subCubes[0][1][2] = ROTATE_LEFT(oldSubCubes[2][1][2]);
	m_subCubes[1][1][2] = ROTATE_LEFT(oldSubCubes[2][1][1]);
	m_subCubes[2][1][2] = ROTATE_LEFT(oldSubCubes[2][1][0]);
	Di(); // rotate the Down face counter-clockwise
}

void CubeModel::rotateRight()
{
	Ui(); // rotate the Up face counter-clockwise
	cubes_t oldSubCubes(m_subCubes);
    // rotate the right face clockwise
	m_subCubes[0][1][0] = ROTATE_RIGHT(oldSubCubes[2][1][0]);
	m_subCubes[1][1][0] = ROTATE_RIGHT(oldSubCubes[2][1][1]);
	m_subCubes[2][1][0] = ROTATE_RIGHT(oldSubCubes[2][1][2]);
	m_subCubes[0][1][1] = ROTATE_RIGHT(oldSubCubes[1][1][0]);
	m_subCubes[1][1][1] = ROTATE_RIGHT(oldSubCubes[1][1][1]);
	m_subCubes[2][1][1] = ROTATE_RIGHT(oldSubCubes[1][1][2]);
	m_subCubes[0][1][2] = ROTATE_RIGHT(oldSubCubes[0][1][0]);
	m_subCubes[1][1][2] = ROTATE_RIGHT(oldSubCubes[0][1][1]);
	m_subCubes[2][1][2] = ROTATE_RIGHT(oldSubCubes[0][1][2]);
	D(); // rotate the Down face clockwise

}

void CubeModel::rotateUp()
{
	Li(); // rotate the Left face counter-clockwise
	cubes_t oldSubCubes(m_subCubes);
    // rotate the Up face clockwise
	m_subCubes[1][0][0] = ROTATE_UP(oldSubCubes[1][2][0]);
	m_subCubes[1][0][1] = ROTATE_UP(oldSubCubes[1][1][0]);
	m_subCubes[1][0][2] = ROTATE_UP(oldSubCubes[1][0][0]);
	m_subCubes[1][1][0] = ROTATE_UP(oldSubCubes[1][2][1]);
	m_subCubes[1][1][1] = ROTATE_UP(oldSubCubes[1][1][1]);
	m_subCubes[1][1][2] = ROTATE_UP(oldSubCubes[1][0][1]);
	m_subCubes[1][2][0] = ROTATE_UP(oldSubCubes[1][2][2]);
	m_subCubes[1][2][1] = ROTATE_UP(oldSubCubes[1][1][2]);
	m_subCubes[1][2][2] = ROTATE_UP(oldSubCubes[1][0][2]);
	R(); // rotate the Right face clockwise
}

void CubeModel::rotateDown()
{
	L(); // rotate the Left face clockwise
	cubes_t oldSubCubes(m_subCubes);
    // rotate the Down face clockwise
	m_subCubes[1][0][0] = ROTATE_DOWN(oldSubCubes[1][0][2]);
	m_subCubes[1][0][1] = ROTATE_DOWN(oldSubCubes[1][1][2]);
	m_subCubes[1][0][2] = ROTATE_DOWN(oldSubCubes[1][2][2]);
	m_subCubes[1][1][0] = ROTATE_DOWN(oldSubCubes[1][0][1]);
	m_subCubes[1][1][1] = ROTATE_DOWN(oldSubCubes[1][1][1]);
	m_subCubes[1][1][2] = ROTATE_DOWN(oldSubCubes[1][2][1]);
	m_subCubes[1][2][0] = ROTATE_DOWN(oldSubCubes[1][0][0]);
	m_subCubes[1][2][1] = ROTATE_DOWN(oldSubCubes[1][1][0]);
	m_subCubes[1][2][2] = ROTATE_DOWN(oldSubCubes[1][2][0]);
	Ri(); // rotate the Right face counter-clockwise
}

void CubeModel::rotateClockwise()
{
	F(); // rotate the Front face clockwise
	cubes_t oldSubCubes(m_subCubes);
    // rotate the Up face clockwise
	m_subCubes[0][0][1] = ROTATE_CLK(oldSubCubes[2][0][1]);
	m_subCubes[1][0][1] = ROTATE_CLK(oldSubCubes[2][1][1]);
	m_subCubes[2][0][1] = ROTATE_CLK(oldSubCubes[2][2][1]);
	m_subCubes[0][1][1] = ROTATE_CLK(oldSubCubes[1][0][1]);
	m_subCubes[1][1][1] = ROTATE_CLK(oldSubCubes[1][1][1]);
	m_subCubes[2][1][1] = ROTATE_CLK(oldSubCubes[1][2][1]);
	m_subCubes[0][2][1] = ROTATE_CLK(oldSubCubes[0][0][1]);
	m_subCubes[1][2][1] = ROTATE_CLK(oldSubCubes[0][1][1]);
	m_subCubes[2][2][1] = ROTATE_CLK(oldSubCubes[0][2][1]);
	Bi(); // rotate the Back face counter-clockwise
}

void CubeModel::rotateCounterClockwise()
{
	Fi(); // rotate the Front face counter-clockwise
	cubes_t oldSubCubes(m_subCubes);
    // rotate the Up face counter-clockwise
	m_subCubes[0][0][1] = ROTATE_CCLK(oldSubCubes[0][2][1]);
	m_subCubes[1][0][1] = ROTATE_CCLK(oldSubCubes[0][1][1]);
	m_subCubes[2][0][1] = ROTATE_CCLK(oldSubCubes[0][0][1]);
	m_subCubes[0][1][1] = ROTATE_CCLK(oldSubCubes[1][2][1]);
	m_subCubes[1][1][1] = ROTATE_CCLK(oldSubCubes[1][1][1]);
	m_subCubes[2][1][1] = ROTATE_CCLK(oldSubCubes[1][0][1]);
	m_subCubes[0][2][1] = ROTATE_CCLK(oldSubCubes[2][2][1]);
	m_subCubes[1][2][1] = ROTATE_CCLK(oldSubCubes[2][1][1]);
	m_subCubes[2][2][1] = ROTATE_CCLK(oldSubCubes[2][0][1]);
	B(); // rotate the Back face clockwise
}
