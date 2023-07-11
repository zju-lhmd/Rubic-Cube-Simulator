#ifndef RENDERER_H
#define RENDERER_H

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include "../../COMMON/config.h" // common
#include "../../COMMON/types.h" // common
#include "../../COMMON/macro.h" // common

class MainWindow;

class Renderer {
public:
    Renderer(MainWindow* pV);
    ~Renderer();

    void incViewAngleX(GLfloat dx);
    void incViewAngleY(GLfloat dy);

    int getRenderState(); // only used for debug
    void setRenderState(int state);

    void switchViewMode();

    void render();

private:
    // only be called by Renderer::render()
    void setColor(CubeColor);
    void renderSubCube(GLfloat, GLfloat, GLfloat, cube_t);
    void renderCube(cubes_t& cube);
    void renderCubeRange(cubes_t& cube, int, int, int, int, int, int);
    void renderCube(cubes_t& cube, float, CubeRotateMethod);

private:
    MainWindow* m_pV;
    // view data
    int m_renderState;
    GLfloat m_viewAngleX, m_viewAngleY;
    bool m_isTransparent;

private:
    // vertex and edge data
    static const GLfloat s_vertexData[];
    static const GLfloat s_edgeData[];
};

#endif