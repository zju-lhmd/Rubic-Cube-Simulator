#include "EventCallback.h"

#include "../MainWindow.h"

EventCallback::EventCallback(MainWindow* pV)
: m_pV(pV),
  m_commandBuffer(""),
  m_lastX(0.0), m_lastY(0.0),
  m_mouseDown(false)
{
}

EventCallback::~EventCallback()
{
}

std::string EventCallback::getCommandBuffer()
{
	return m_commandBuffer;
}

void EventCallback::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		glfwGetCursorPos(window, &m_lastX, &m_lastY);
		m_mouseDown = true;
	}else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		m_mouseDown = false;
		glfwGetCursorPos(window, &m_lastX, &m_lastX);
	}
}

void EventCallback::mouseMove()
{
	if (!m_mouseDown) return; // mouse not pressed

	double currX, currY;
	glfwGetCursorPos(m_pV->m_pWindow, &currX, &currY); //get current mouse coordinate

	double dX = currX - m_lastX, dY = currY - m_lastY;

	m_pV->m_pRenderer->incViewAngleY(dX * 0.5); // updates the Y rotation angle of the view
    m_pV->m_pRenderer->incViewAngleX(dY * 0.5); // updates the X rotation angle of the view

	m_pV->m_pRenderer->setRenderState(1);
	m_lastX = currX; m_lastY = currY;
}

void EventCallback::execCommand(std::string cmd)
{
	std::string param("");
	size_t index = cmd.find(' ');
	if (index != std::string::npos) {
		param = cmd.substr(index + 1);
		cmd = cmd.substr(0, index);
	}
	cmd = toUpperString(cmd); // converts the command to uppercase for case-insensitive comparisons

	// execute different commands
	if(cmd == "TRAN")
		m_pV->m_pRenderer->switchViewMode(); // switches the view mode
	else if(cmd == "RESET") {
		m_pV->m_pResetHandler->exec();
	}else if(cmd == "RANDOM") {
		m_pV->m_pRandomHandler->exec();
	}else if(cmd == "SOLVE") {
		m_pV->m_pSolveHandler->exec();
	}else if(cmd == "STOP") {
		m_pV->m_pStopHandler->exec();
	}else if(cmd == "SAVE") {
		m_pV->m_pSaveHandler->setParameter(param);
		m_pV->m_pSaveHandler->exec();
	}else if(cmd == "LOAD") {
		m_pV->m_pLoadHandler->setParameter(param);
		m_pV->m_pLoadHandler->exec();
	}else { // rotation commands
		m_pV->m_pRotateHandler->setParameter(cmd);
		m_pV->m_pRotateHandler->exec();
	}
}

void EventCallback::keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		if (key == GLFW_KEY_BACKSPACE) { //if a " " is entered.
			if (m_commandBuffer.length() > 0) {
				m_commandBuffer = m_commandBuffer.substr(0, m_commandBuffer.length() - 1);
			}
		}else if (key == GLFW_KEY_ENTER || key == GLFW_KEY_KP_ENTER) { //if a new line is enterd
			execCommand(m_commandBuffer); // executes the command in the command buffer
			m_commandBuffer.clear(); // clears the command buffer
		}
	}
}

void EventCallback::characterCallback(GLFWwindow *window, unsigned int codepoint)
{
	if (codepoint < 256) {
		char ch = (char)codepoint;
		m_commandBuffer += ch; // appends the character to the command buffer
	}
}

void EventCallback::keyboardScan()
{
	if(glfwGetKey(m_pV->m_pWindow, GLFW_KEY_LEFT) == GLFW_PRESS) { // move left
		m_pV->m_pRenderer->incViewAngleY(-0.11f);
		m_pV->m_pRenderer->setRenderState(1);
	}
	if(glfwGetKey(m_pV->m_pWindow, GLFW_KEY_RIGHT) == GLFW_PRESS) { // move right
        m_pV->m_pRenderer->incViewAngleY(0.11f);
		m_pV->m_pRenderer->setRenderState(1);
	}
	if(glfwGetKey(m_pV->m_pWindow, GLFW_KEY_UP) == GLFW_PRESS) { // move up
        m_pV->m_pRenderer->incViewAngleX(-0.15f);
		m_pV->m_pRenderer->setRenderState(1);
	}
	if(glfwGetKey(m_pV->m_pWindow, GLFW_KEY_DOWN) == GLFW_PRESS) { // move down
        m_pV->m_pRenderer->incViewAngleX(0.15f);
		m_pV->m_pRenderer->setRenderState(1);
	}
}