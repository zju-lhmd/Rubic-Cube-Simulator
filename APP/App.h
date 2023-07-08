#ifndef APP_H
#define APP_H

#include <ctime>
#include <cstdlib>

#include "../VIEW/MainWindow.h" // view
#include "../VIEWMODEL/CommandHandlers.h" // viewmodel
#include "../MODEL/Cube.h" // model

// Rubic Cube Simulator App
class App {
public:
    App();

    ~App();
    // Run app
    void Run();
private:
    // model
    Cube m_cube;
    // viewmodel
    CommandHandler m_commandhandler;
    // view
    MainWindow m_window;
};


#endif
