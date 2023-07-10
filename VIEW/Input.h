#ifndef INPUT_H
#define INPUT_H

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <string>

#include "Rendering.h" // view
#include "../VIEWMODEL/CommandHandlers.h" // viewmodel

class EventHandler {
public:
    EventHandler(CommandHandler* commandhandler = nullptr,
                 GLFWwindow* window = nullptr,
                 Renderer* renderer = nullptr);

    ~EventHandler();

    void SetWindow(GLFWwindow* window);
    void SetCommandHandler(CommandHandler* commandhandler);
    void SetRenderer(Renderer* renderer);

    // event callback
    void mouseButtonCallback(GLFWwindow*, int, int, int);// Callback for mouse button events
    void keyboardCallback(GLFWwindow*, int, int, int, int);// Callback for keyboard events
    void characterCallback(GLFWwindow*, unsigned int);// Callback for character input events
    // state update
    void mouseMove();
    void keyboardScan();

    std::string getCommand();
private:
    // execute command
    void execCommand(std::string);
    // reference
    GLFWwindow* m_windowRef;
    Renderer* m_rendererRef;
    CommandHandler* m_commandHandlerRef;
    // command buffer
    std::string m_commandBuffer;// Buffer to store the entered command
    // mouse state
    double lastX, lastY;// Coordinates of the last mouse position
    bool mouseDown;// Flag indicating if the mouse button is pressed
    double lastAngleX, lastAngleY;// Last rotation angles
};

#endif