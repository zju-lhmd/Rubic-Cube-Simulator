#ifndef COMMANDHANDLERS_H
#define COMMANDHANDLERS_H

#include <fstream>

#include "../COMMON/utilities.h" // common
#include "../MODEL/Cube.h" // model
#include "RotateController.h" // viewmodel

class CommandHandler {
public:
    CommandHandler(Cube* c);

    ~CommandHandler();

    bool init();
    // execute command
    void testHandler();
    void resetHandler();
    void randomHandler();
    void solveHandler();
    void stopHandler();
    void saveHandler(std::string value);
    void loadHandler(std::string value);
    void rotateHandler(std::string value);

    inline RotateController* GetRotateController() {
        return &rotateController;
    }

private:
    Cube* cube;
    RotateController rotateController;

};

#endif