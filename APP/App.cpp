#include "App.h"


App::App()
{
}

App::~App()
{
}

bool App::init()
{
    // model & viewmodel
    m_pCubeModel = std::make_shared<Cube>();
    m_pViewModel = std::make_shared<ViewModel>();
    m_pViewModel->init();
    m_pViewModel->setCubeModel(m_pCubeModel);
    // view
    if(!m_mainWindow.init()) return false; // failed to init main window
    // binding
    // properties
    m_mainWindow.setCube(m_pViewModel->getCubeData());
    m_mainWindow.setRSteps(m_pViewModel->getSteps());
    // commands
    m_mainWindow.setResetHandler(m_pViewModel->getResetCmd());
    m_mainWindow.setRandomHandler(m_pViewModel->getRandomCmd());
    m_mainWindow.setRotateHandler(m_pViewModel->getRotateCmd());
    m_mainWindow.setSaveHandler(m_pViewModel->getSaveCmd());
    m_mainWindow.setLoadHandler(m_pViewModel->getLoadCmd());
    m_mainWindow.setSolveHandler(m_pViewModel->getSolveCmd());
    m_mainWindow.setStopHandler(m_pViewModel->getStopCmd());
    m_mainWindow.setRotEndHandler(m_pViewModel->getRotEndCmd());
    // notifications
    m_pViewModel->addObserver(m_mainWindow.getSink());
    return true;
}

void App::Run()
{
    m_mainWindow.show();
}