#ifndef APP_H
#define APP_H

#include <ctime>
#include <cstdlib>
#include <memory>

#include "../VIEW/MainWindow.h" // view
#include "../VIEWMODEL/ViewModel.h" // viewmodel
#include "../MODEL/Cube.h" // model

// Rubic Cube Simulator App
class App {
public:
    App();

    ~App();
    // init app
    bool init();
    // Run app
    void Run();

private:
    // model
    std::shared_ptr<Cube> m_pCubeModel;
    // viewmodel
    std::shared_ptr<ViewModel> m_pViewModel;
    // view
    MainWindow m_mainWindow;
};


#endif
