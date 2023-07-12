#include "MainWindowSink.h"

#include "../MainWindow.h"

MainWindowSink::MainWindowSink(MainWindow* pV): m_pV(pV)
{
}

void MainWindowSink::notify(const std::any& msg)
{
    // TODO: react to notifications
    int state = std::any_cast<int>(msg);
    switch(state) {
        case 2: m_pV->m_pRotAni->play(); break;
        case 1: m_pV->m_pRenderer->setRenderState(state); break;
        case 0: m_pV->m_pRotAni->stopPlay(); break;
    }
    return ;
}