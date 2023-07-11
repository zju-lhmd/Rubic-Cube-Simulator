#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <cmath>
#include <memory>

#include "../COMMON/config.h" // common
#include "../COMMON/types.h" // common
#include "../COMMON/ICommandBase.h" // common
#include "../COMMON/INotification.h" // common
#include "../COMMON/Notification.h" // common
// view
#include "sinks/MainWindowSink.h"
#include "rotani/RotAni.h"
#include "render/Renderer.h"
#include "events/EventCallback.h"

// Main window of app using OPENGL
class MainWindow : public Notification {
public:
    MainWindow();

    ~MainWindow();

    bool init(); // Initialize the main window

    void show(); // Display the main window

    std::shared_ptr<INotification> getSink();

    void setCube(std::shared_ptr<cubes_t> cubes);
    void setRSteps(std::shared_ptr<CubeSteps> steps);

    void setResetHandler(std::shared_ptr<ICommandBase> reset);
    void setRandomHandler(std::shared_ptr<ICommandBase> random);
    void setRotateHandler(std::shared_ptr<ICommandBase> rotate);
    void setSaveHandler(std::shared_ptr<ICommandBase> save);
    void setLoadHandler(std::shared_ptr<ICommandBase> load);
    void setSolveHandler(std::shared_ptr<ICommandBase> solve);
    void setStopHandler(std::shared_ptr<ICommandBase> stop);

private:
    // only called in MainWindow::init()
    void initGL();
    // only called in MainWindow::initGL()
    void createViewMatrix(float eyeX, float eyeY, float eyeZ,
                     float centerX, float centerY, float centerZ,
                     float upX, float upY, float upZ,
                     float* viewMatrix); // create a view matrix

private:
    // properties
    std::shared_ptr<cubes_t> m_pCubeData;
    std::shared_ptr<CubeSteps> m_pRSteps;

    // commands handlers
    std::shared_ptr<ICommandBase> m_pResetHandler;
    std::shared_ptr<ICommandBase> m_pRandomHandler;
    std::shared_ptr<ICommandBase> m_pRotateHandler;
    std::shared_ptr<ICommandBase> m_pSaveHandler;
    std::shared_ptr<ICommandBase> m_pLoadHandler;
    std::shared_ptr<ICommandBase> m_pSolveHandler;
    std::shared_ptr<ICommandBase> m_pStopHandler;

    // sinks
    std::shared_ptr<MainWindowSink> m_pVS;

private:
    GLFWwindow* m_pWindow; // pointer to the GLFW window
    std::shared_ptr<Renderer> m_pRenderer;
    std::shared_ptr<EventCallback> m_pEventCallback;
    std::shared_ptr<RotAni> m_pRotAni;

private:
    friend class MainWindowSink;
    friend class Renderer;
    friend class EventCallback;
    friend class RotAni;
};


#endif
