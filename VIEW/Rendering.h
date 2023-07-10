#ifndef RENDERING_H
#define RENDERING_H

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include "../COMMON/Config.h" // common
#include "../VIEWMODEL/RotateController.h" // viewmodel

class Renderer {
public:
    Renderer(
            RotateController* rotateControllerRef = nullptr,
            GLfloat angleX = DEFAULT_VIEW_ANGLE_X,
            GLfloat angleY = DEFAULT_VIEW_ANGLE_Y);
    ~Renderer();

    void SetRotateController(RotateController* rc);

    GLfloat GetViewRotationAngleX();
    GLfloat GetViewRotationAngleY();

    void SetViewRotationAngleX(GLfloat angleX);
    void SetViewRotaionAngleY(GLfloat angleY);

    void incViewRotationAngleX(GLfloat dx);
    void incViewRotationAngleY(GLfloat dy);

    void SwitchViewMode();

    void render(const std::string& text);

    RotateController* GetRotateController();

    // void Renderer::renderText(const std::string& text, float x, float y, float scale);

private:
    // Only be called by Renderer::render()
    void setColor(CubeColor);
    void renderSubCube(GLfloat, GLfloat, GLfloat, cube_t);
    void renderCube(cubes_t& cube);
    void renderCubeRange(cubes_t& cube, int, int, int, int, int, int);
    void renderCube(cubes_t& cube, float, CubeRotateMethod);
    // reference
    RotateController* rotateControllerRef;

    GLfloat m_viewRotationAngleX, m_viewRotationAngleY;
    bool isTransparent;
    // vertex and edge data
    static const GLfloat VertexData[];
    static const GLfloat EdgeData[];

    // FT_Library m_ftLibrary;  // FreeType库对象
    // FT_Face m_fontFace;  // 字体Face对象
    // ...
    // void initFreeType();
    // void destroyFreeType();
    // void renderText(const std::string& text, float x, float y, float scale);

};

#endif