#include "Input.h"

EventHandler::EventHandler(CommandHandler* commandhandler,
						   GLFWwindow* window, Renderer* renderer)
    : m_windowRef(window),
      m_rendererRef(renderer),
      m_commandHandlerRef(commandhandler),
      m_commandBuffer(""),
      lastX(0.0), lastY(0.0),
      mouseDown(false),
      lastAngleX(0.0), lastAngleY(0.0)
{
}

EventHandler::~EventHandler()
{
}

void EventHandler::SetWindow(GLFWwindow* window)
{
    m_windowRef = window;
}

void EventHandler::SetCommandHandler(CommandHandler* commandhandler)
{
    m_commandHandlerRef = commandhandler;
}

void EventHandler::SetRenderer(Renderer* renderer)
{
    m_rendererRef = renderer;
}

void EventHandler::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // Set angle
		lastAngleX = m_rendererRef->GetViewRotationAngleX();
		lastAngleY = m_rendererRef->GetViewRotationAngleY();
		glfwGetCursorPos(window, &lastX, &lastY);
		mouseDown = true;
	}else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		mouseDown = false;
		glfwGetCursorPos(window, &lastX, &lastX);
	}
}

void EventHandler::mouseMove()
{
	if (!mouseDown) return; // Mouse not pressed

	double currX, currY;
	glfwGetCursorPos(m_windowRef, &currX, &currY);//get current mouse coordinate

	double deltaX = currX - lastX,
		   deltaY = currY - lastY;

	m_rendererRef->SetViewRotaionAngleY(lastAngleY + deltaX * 0.5);// Updates the Y rotation angle of the view
    m_rendererRef->SetViewRotationAngleX(lastAngleX + deltaY * 0.5);// Updates the X rotation angle of the view
}

void EventHandler::execCommand(std::string cmd)
{
	try {
		std::string value("");
		size_t index = cmd.find(' ');
		if (index != std::string::npos) {
			value = cmd.substr(index + 1);
			cmd = cmd.substr(0, index);
		}
		cmd = toUpperString(cmd);// Converts the command to uppercase for case-insensitive comparisons

        // execute different command
        if(cmd == "TRAN")
            m_rendererRef->SwitchViewMode();// Switches the view mode
        else if(cmd == "TSET")
            m_commandHandlerRef->testHandler();
        else if(cmd == "RESET")
            m_commandHandlerRef->resetHandler();
        else if(cmd == "RANDOM")
            m_commandHandlerRef->randomHandler();
        else if(cmd == "SOLVE")
            m_commandHandlerRef->solveHandler();
        else if(cmd == "STOP")
            m_commandHandlerRef->stopHandler();
        else if(cmd == "SAVE")
            m_commandHandlerRef->saveHandler(value);
        else if(cmd == "LOAD")
            m_commandHandlerRef->loadHandler(value);
        else // rotation commands
            m_commandHandlerRef->rotateHandler(cmd);
	}catch(const SolverError &err) {
		printError(err);// Prints the solver error message
	}catch(const CubeError &err) {
		printError(err);// Prints the cube error message
	}
}

void EventHandler::keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		if (key == GLFW_KEY_BACKSPACE) {//if a " " is entered.
			if (m_commandBuffer.length() > 0) {
				m_commandBuffer = m_commandBuffer.substr(0, m_commandBuffer.length() - 1);
			}
			printf("\r%s ", m_commandBuffer.c_str()); // TODO
			printf("\r%s", m_commandBuffer.c_str());// Prints the modified command on the console
		}else if (key == GLFW_KEY_ENTER || key == GLFW_KEY_KP_ENTER) { //if a new line is enterd
			// printf("\n");
			double start = glfwGetTime();
			execCommand(m_commandBuffer);// Executes the command in the command buffer
			// printf("\nDone(%.4f ms).\n", (glfwGetTime() - start) * 1000);
			m_commandBuffer.clear();// Clears the command buffer
		}
	}
}

std::string EventHandler::getCommand()
{
	return m_commandBuffer;
}

void EventHandler::characterCallback(GLFWwindow *window, unsigned int codepoint)
{
	if (codepoint < 256) {
		char ch = (char)codepoint;
		m_commandBuffer += ch;// Appends the character to the command buffer
		// printf("%c", ch);// Prints the character on the console

	}
}

void EventHandler::keyboardScan()
{
	if (glfwGetKey(m_windowRef, GLFW_KEY_LEFT) == GLFW_PRESS) { // move left
		m_rendererRef->incViewRotationAngleY(-0.5f);
	}
	if (glfwGetKey(m_windowRef, GLFW_KEY_RIGHT) == GLFW_PRESS) { // move right
        m_rendererRef->incViewRotationAngleY(0.5f);
	}
	if (glfwGetKey(m_windowRef, GLFW_KEY_UP) == GLFW_PRESS) { // move up
        m_rendererRef->incViewRotationAngleX(-0.5f);
	}
	if (glfwGetKey(m_windowRef, GLFW_KEY_DOWN) == GLFW_PRESS) { // move down
        m_rendererRef->incViewRotationAngleX(0.5f);
	}
}