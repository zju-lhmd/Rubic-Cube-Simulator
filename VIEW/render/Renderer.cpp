#include "Renderer.h"

#include "../MainWindow.h"

Renderer::Renderer(MainWindow* pV)
: m_pV(pV), m_renderState(1),
  m_viewAngleX(DEFAULT_VIEW_ANGLE_X), m_viewAngleY(DEFAULT_VIEW_ANGLE_Y),
  m_isTransparent(false)
{
}

Renderer::~Renderer()
{
}

void Renderer::incViewAngleX(GLfloat dx)
{
    m_viewAngleX += dx;
}

void Renderer::incViewAngleY(GLfloat dy)
{
    m_viewAngleY += dy;
}

void Renderer::switchViewMode()
{
    m_isTransparent = !m_isTransparent;
}

int Renderer::getRenderState()
{
	return m_renderState;
}

void Renderer::setRenderState(int state)
{
	m_renderState = state;
}

void Renderer::setColor(CubeColor color)
{
	GLfloat alpha = 1.0f;
	if(m_isTransparent) {
		alpha = 0.5f;
	}

	switch (color) {
	case COLOR_UNUSED:
		glColor4f(RGB_GRAY, alpha);
		break;
	case COLOR_BLUE:
		glColor4f(RGB_BLUE, alpha);
		break;
	case COLOR_GREEN:
		glColor4f(RGB_GREEN, alpha);
		break;
	case COLOR_ORANGE:
		glColor4f(RGB_ORANGE, alpha);
		break;
	case COLOR_RED:
		glColor4f(RGB_RED, alpha);
		break;
	case COLOR_WHITE:
		glColor4f(RGB_WHITE, alpha);
		break;
	case COLOR_YELLOW:
		glColor4f(RGB_YELLOW, alpha);
		break;
	default:
		break;
	}
}

void Renderer::renderSubCube(GLfloat x, GLfloat y, GLfloat z, cube_t colorInfo)
{
	glPushMatrix();
	glTranslatef(-1.6f, -1.6f, -1.6f);

	glPushMatrix();
	glTranslatef(1.1f * x, 1.1f * y, 1.1f * z);

	setColor((CubeColor)GET_FRONT(colorInfo));
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 6; ++i) {
		glVertex3f(s_vertexData[i * 3 + 0],
			s_vertexData[i * 3 + 1],
			s_vertexData[i * 3 + 2]);
	}
	glEnd();

	setColor((CubeColor)GET_BACK(colorInfo));
	glBegin(GL_TRIANGLES);
	for (int i = 6; i < 12; ++i) {
		glVertex3f(s_vertexData[i * 3 + 0],
			s_vertexData[i * 3 + 1],
			s_vertexData[i * 3 + 2]);
	}
	glEnd();

	setColor((CubeColor)GET_LEFT(colorInfo));
	glBegin(GL_TRIANGLES);
	for (int i = 12; i < 18; ++i) {
		glVertex3f(s_vertexData[i * 3 + 0],
			s_vertexData[i * 3 + 1],
			s_vertexData[i * 3 + 2]);
	}
	glEnd();

	setColor((CubeColor)GET_RIGHT(colorInfo));
	glBegin(GL_TRIANGLES);
	for (int i = 18; i < 24; ++i) {
		glVertex3f(s_vertexData[i * 3 + 0],
			s_vertexData[i * 3 + 1],
			s_vertexData[i * 3 + 2]);
	}
	glEnd();

	setColor((CubeColor)GET_UP(colorInfo));
	glBegin(GL_TRIANGLES);
	for (int i = 24; i < 30; ++i) {
		glVertex3f(s_vertexData[i * 3 + 0],
			s_vertexData[i * 3 + 1],
			s_vertexData[i * 3 + 2]);
	}
	glEnd();

	setColor((CubeColor)GET_DOWN(colorInfo));
	glBegin(GL_TRIANGLES);
	for (int i = 30; i < 36; ++i) {
		glVertex3f(s_vertexData[i * 3 + 0],
			s_vertexData[i * 3 + 1],
			s_vertexData[i * 3 + 2]);
	}
	glEnd();

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	for (int i = 0; i < 24; ++i) {
		glVertex3f(s_edgeData[i * 3 + 0],
			s_edgeData[i * 3 + 1],
			s_edgeData[i * 3 + 2]);
	}
	glEnd();

	glPopMatrix();

	glPopMatrix();
}

void Renderer::renderCube(cubes_t& cube)
{
	glPushMatrix();
	glTranslatef(-1.6f, -1.6f, -1.6f);
	for (int x = 0; x <= 2; ++x) {
		for (int y = 0; y <= 2; ++y) {
			for (int z = 0; z <= 2; ++z) {
				renderSubCube((GLfloat)x, (GLfloat)y, (GLfloat)z, cube[x][y][z]);
			}
		}
	}
	glPopMatrix();
}

inline void Renderer::renderCubeRange(cubes_t& cube, int x0, int x1, int y0, int y1, int z0, int z1)
{
	for (int x = x0; x <= x1; ++x) {
		for (int y = y0; y <= y1; ++y) {
			for (int z = z0; z <= z1; ++z) {
				renderSubCube((GLfloat)x, (GLfloat)y, (GLfloat)z, cube[x][y][z]);
			}
		}
	}
}

void Renderer::renderCube(cubes_t& cube, float angle, CubeRotateMethod method)
{
	switch (method) {
	case ROTATE_FRONT:
		glPushMatrix();
		glRotatef(angle, 0.0, 0.0, -1.0);
		renderCubeRange(cube, 0, 2, 0, 2, 2, 2);
		glPopMatrix();
		renderCubeRange(cube, 0, 2, 0, 2, 0, 1);
		break;
	case ROTATE_BACK:
		glPushMatrix();
		glRotatef(angle, 0.0, 0.0, 1.0);
		renderCubeRange(cube, 0, 2, 0, 2, 0, 0);
		glPopMatrix();
		renderCubeRange(cube, 0, 2, 0, 2, 1, 2);
		break;
	case ROTATE_LEFT:
		glPushMatrix();
		glRotatef(angle, 1.0, 0.0, 0.0);
		renderCubeRange(cube, 0, 0, 0, 2, 0, 2);
		glPopMatrix();
		renderCubeRange(cube, 1, 2, 0, 2, 0, 2);
		break;
	case ROTATE_RIGHT:
		glPushMatrix();
		glRotatef(angle, -1.0, 0.0, 0.0);
		renderCubeRange(cube, 2, 2, 0, 2, 0, 2);
		glPopMatrix();
		renderCubeRange(cube, 0, 1, 0, 2, 0, 2);
		break;
	case ROTATE_UP:
		glPushMatrix();
		glRotatef(angle, 0.0, -1.0, 0.0);
		renderCubeRange(cube, 0, 2, 2, 2, 0, 2);
		glPopMatrix();
		renderCubeRange(cube, 0, 2, 0, 1, 0, 2);
		break;
	case ROTATE_DOWN:
		glPushMatrix();
		glRotatef(angle, 0.0, 1.0, 0.0);
		renderCubeRange(cube, 0, 2, 0, 0, 0, 2);
		glPopMatrix();
		renderCubeRange(cube, 0, 2, 1, 2, 0, 2);
		break;
	case ROTATE_WHOLEX:
		glPushMatrix();
		glRotatef(angle, -1.0, 0.0, 0.0);
		renderCubeRange(cube, 0, 2, 0, 2, 0, 2);
		glPopMatrix();
		break;
	case ROTATE_WHOLEY:
		glPushMatrix();
		glRotatef(angle, 0.0, -1.0, 0.0);
		renderCubeRange(cube, 0, 2, 0, 2, 0, 2);
		glPopMatrix();
		break;
	case ROTATE_WHOLEZ:
		glPushMatrix();
		glRotatef(angle, 0.0, 0.0, -1.0);
		renderCubeRange(cube, 0, 2, 0, 2, 0, 2);
		glPopMatrix();
		break;
	case ROTATE_FRONTi:
		glPushMatrix();
		glRotatef(angle, 0.0, 0.0, 1.0);
		renderCubeRange(cube, 0, 2, 0, 2, 2, 2);
		glPopMatrix();
		renderCubeRange(cube, 0, 2, 0, 2, 0, 1);
		break;
	case ROTATE_BACKi:
		glPushMatrix();
		glRotatef(angle, 0.0, 0.0, -1.0);
		renderCubeRange(cube, 0, 2, 0, 2, 0, 0);
		glPopMatrix();
		renderCubeRange(cube, 0, 2, 0, 2, 1, 2);
		break;
	case ROTATE_LEFTi:
		glPushMatrix();
		glRotatef(angle, -1.0, 0.0, 0.0);
		renderCubeRange(cube, 0, 0, 0, 2, 0, 2);
		glPopMatrix();
		renderCubeRange(cube, 1, 2, 0, 2, 0, 2);
		break;
	case ROTATE_RIGHTi:
		glPushMatrix();
		glRotatef(angle, 1.0, 0.0, 0.0);
		renderCubeRange(cube, 2, 2, 0, 2, 0, 2);
		glPopMatrix();
		renderCubeRange(cube, 0, 1, 0, 2, 0, 2);
		break;
	case ROTATE_UPi:
		glPushMatrix();
		glRotatef(angle, 0.0, 1.0, 0.0);
		renderCubeRange(cube, 0, 2, 2, 2, 0, 2);
		glPopMatrix();
		renderCubeRange(cube, 0, 2, 0, 1, 0, 2);
		break;
	case ROTATE_DOWNi:
		glPushMatrix();
		glRotatef(angle, 0.0, -1.0, 0.0);
		renderCubeRange(cube, 0, 2, 0, 0, 0, 2);
		glPopMatrix();
		renderCubeRange(cube, 0, 2, 1, 2, 0, 2);
		break;
	case ROTATE_WHOLEXi:
		glPushMatrix();
		glRotatef(angle, 1.0, 0.0, 0.0);
		renderCubeRange(cube, 0, 2, 0, 2, 0, 2);
		glPopMatrix();
		break;
	case ROTATE_WHOLEYi:
		glPushMatrix();
		glRotatef(angle, 0.0, 1.0, 0.0);
		renderCubeRange(cube, 0, 2, 0, 2, 0, 2);
		glPopMatrix();
		break;
	case ROTATE_WHOLEZi:
		glPushMatrix();
		glRotatef(angle, 0.0, 0.0, 1.0);
		renderCubeRange(cube, 0, 2, 0, 2, 0, 2);
		glPopMatrix();
		break;
	default:
		renderCubeRange(cube, 0, 2, 0, 2, 0, 2);
		break;
	}
}

void Renderer::render()
{
	if(m_renderState > 0) {
		// render background
		if(m_renderState == 1) m_renderState = 0; // just update
		glClearColor(BACKGROUND_COLOR);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// flush screen
		glFlush();
		// set view rotation model
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -10.0f);
		glPushMatrix();
		glRotatef(m_viewAngleX, 1.0f, 0.0f, 0.0f);
		glPushMatrix();
		glRotatef(m_viewAngleY, 0.0f, 1.0f, 0.0f);
		// render cube
		cubes_t cube = *(m_pV->m_pCubeData);
		renderCube(cube, 
				(GLfloat)(m_pV->m_pRotAni->getRotAngle()), 
				m_pV->m_pRotAni->getRotMethod());
		// pop model
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
		// flush screen
		glFlush();
		// swap buffers
		glfwSwapBuffers(m_pV->m_pWindow);
	}
}

const GLfloat Renderer::s_vertexData[] = {
        // Front Face (2 triangles)
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        // Back Face (2 triangles)
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        // Left Face (2 triangles)
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        // Right Face (2 triangles)
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        // Up Face (2 triangles)
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,
        // Down Face (2 triangles)
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f
};

const GLfloat Renderer::s_edgeData[] = {
        // Every 2 vetexes represents an edge
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f
};
