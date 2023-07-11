#ifndef EVENTCALLBACK_H
#define EVENTCALLBACK_H

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <string>

#include "../../COMMON/utilities.h"

class MainWindow;

class EventCallback {
public:
    EventCallback(MainWindow* pV);

    ~EventCallback();

    std::string getCommandBuffer(); // used for debug
    // event callbacks
    void mouseButtonCallback(GLFWwindow*, int, int, int);
    void keyboardCallback(GLFWwindow*, int, int, int, int);
    void characterCallback(GLFWwindow*, unsigned int);
    // state update
    void mouseMove();
    void keyboardScan();
private:
    // execute command
    void execCommand(std::string);
private:
    MainWindow* m_pV;
    // command buffer
    std::string m_commandBuffer; // buffer to store the entered command
    // mouse state
    double m_lastX, m_lastY; // coordinates of the last mouse position
    bool m_mouseDown; // flag indicating if the mouse button is pressed
};


#endif