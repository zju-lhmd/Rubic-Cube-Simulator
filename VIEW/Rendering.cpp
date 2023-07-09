#include "Rendering.h"

Renderer::Renderer(RotateController* rotateControllerRef, GLfloat angleX, GLfloat angleY)
    : rotateControllerRef(rotateControllerRef), m_viewRotationAngleX(angleX),
      m_viewRotationAngleY(angleY), isTransparent(false)
{
}
Renderer::~Renderer()
{
}

GLfloat Renderer::GetViewRotationAngleX()
{
    return m_viewRotationAngleX;
}

GLfloat Renderer::GetViewRotationAngleY()
{
    return m_viewRotationAngleY;
}

void Renderer::SetViewRotationAngleX(GLfloat angleX)
{
    m_viewRotationAngleX = angleX;
}

void Renderer::SetViewRotaionAngleY(GLfloat angleY)
{
    m_viewRotationAngleY = angleY;
}

void Renderer::incViewRotationAngleX(GLfloat dx)
{
    m_viewRotationAngleX += dx;
}

void Renderer::incViewRotationAngleY(GLfloat dy)
{
    m_viewRotationAngleY += dy;
}

void Renderer::SwitchViewMode()
{
    isTransparent = !isTransparent;
}

void Renderer::SetRotateController(RotateController* rc)
{
    rotateControllerRef = rc;
}

void Renderer::setColor(CubeColor color)
{
	GLfloat alpha = 1.0f;
	if(isTransparent) {
		alpha = 0.5f;
	}

	switch (color) {
	case COLOR_UNUSED:
		glColor4f(0.5f, 0.5f, 0.5f, alpha);
		break;
	case COLOR_BLUE:
		glColor4f(0.0f, 0.0f, 1.0f, alpha);
		break;
	case COLOR_GREEN:
		glColor4f(0.0f, 1.0f, 0.0f, alpha);
		break;
	case COLOR_ORANGE:
		glColor4f(1.0f, 0.5f, 0.0f, alpha);
		break;
	case COLOR_RED:
		glColor4f(1.0f, 0.0f, 0.0f, alpha);
		break;
	case COLOR_WHITE:
		glColor4f(1.0f, 1.0f, 1.0f, alpha);
		break;
	case COLOR_YELLOW:
		glColor4f(1.0f, 1.0f, 0.0f, alpha);
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
		glVertex3f(VertexData[i * 3 + 0],
			VertexData[i * 3 + 1],
			VertexData[i * 3 + 2]);
	}
	glEnd();

	setColor((CubeColor)GET_BACK(colorInfo));
	glBegin(GL_TRIANGLES);
	for (int i = 6; i < 12; ++i) {
		glVertex3f(VertexData[i * 3 + 0],
			VertexData[i * 3 + 1],
			VertexData[i * 3 + 2]);
	}
	glEnd();

	setColor((CubeColor)GET_LEFT(colorInfo));
	glBegin(GL_TRIANGLES);
	for (int i = 12; i < 18; ++i) {
		glVertex3f(VertexData[i * 3 + 0],
			VertexData[i * 3 + 1],
			VertexData[i * 3 + 2]);
	}
	glEnd();

	setColor((CubeColor)GET_RIGHT(colorInfo));
	glBegin(GL_TRIANGLES);
	for (int i = 18; i < 24; ++i) {
		glVertex3f(VertexData[i * 3 + 0],
			VertexData[i * 3 + 1],
			VertexData[i * 3 + 2]);
	}
	glEnd();

	setColor((CubeColor)GET_UP(colorInfo));
	glBegin(GL_TRIANGLES);
	for (int i = 24; i < 30; ++i) {
		glVertex3f(VertexData[i * 3 + 0],
			VertexData[i * 3 + 1],
			VertexData[i * 3 + 2]);
	}
	glEnd();

	setColor((CubeColor)GET_DOWN(colorInfo));
	glBegin(GL_TRIANGLES);
	for (int i = 30; i < 36; ++i) {
		glVertex3f(VertexData[i * 3 + 0],
			VertexData[i * 3 + 1],
			VertexData[i * 3 + 2]);
	}
	glEnd();

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	for (int i = 0; i < 24; ++i) {
		glVertex3f(EdgeData[i * 3 + 0],
			EdgeData[i * 3 + 1],
			EdgeData[i * 3 + 2]);
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

RotateController* Renderer::GetRotateController() {
    return rotateControllerRef;
}

void Renderer::render()
{
    // render background
	glClearColor(BACKGROUND_COLOR);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // flush screen
	glFlush();
    // set view rotation model
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -10.0f);
	glPushMatrix();
	glRotatef(m_viewRotationAngleX, 1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glRotatef(m_viewRotationAngleY, 0.0f, 1.0f, 0.0f);
    // render cube
    cubes_t cube = rotateControllerRef->GetCubeData();
	renderCube(cube,
               (GLfloat)rotateControllerRef->GetRotateAngle(),
               rotateControllerRef->GetRotateMethod());
    // pop model
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
    // flush screen
	glFlush();
}

const GLfloat Renderer::VertexData[] = {
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

const GLfloat Renderer::EdgeData[] = {
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
