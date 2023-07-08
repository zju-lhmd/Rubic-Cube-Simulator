#include "App.h"


App::App()
    : m_cube(), m_commandhandler(&m_cube),
      m_window(&m_commandhandler)
{
}

App::~App()
{
}

void App::Run()
{
    // Initialize command handler
    if(!m_commandhandler.init()) return;
    // Initialize main window
    if(!m_window.init()) return;
    // Show main window
    m_window.show();
}