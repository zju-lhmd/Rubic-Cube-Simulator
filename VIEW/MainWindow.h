#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <cmath>

#include "../COMMON/Config.h" // common
#include "Rendering.h" // view
#include "Input.h" // view
#include "../VIEWMODEL/CommandHandlers.h" // viewmodel

// Main window of app using OPENGL
class MainWindow {
public:
    MainWindow(CommandHandler* cmdhdl);

    ~MainWindow();

    bool init();// Initialize the main window

    void show();// Display the main window

private:
    // Only called in MainWindow::init()
    void initGL();
    // Only called in MainWindow::initGL()
    void createViewMatrix(float eyeX, float eyeY, float eyeZ,
                     float centerX, float centerY, float centerZ,
                     float upX, float upY, float upZ,
                     float* viewMatrix);// Create a view matrix

private:
    bool is_init;// Flag to indicate if the window is initialized
    GLFWwindow* m_window;// Pointer to the GLFW window
    Renderer m_renderer;
    EventHandler m_eventhandler;
};


#endif
