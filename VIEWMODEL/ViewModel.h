#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <ctime>
#include <fstream>
#include <memory>

#include "../COMMON/utilities.h" // common
#include "../COMMON/ICommandBase.h" // common
#include "../COMMON/Notification.h" // common
#include "../MODEL/Cube.h" // model
// viewmodel (commands)
#include "commands/RotateCommand.h"
#include "commands/ResetCommand.h"
#include "commands/RandomCommand.h"
#include "commands/SolveCommand.h"
#include "commands/StopCommand.h"
#include "commands/SaveCommand.h"
#include "commands/LoadCommand.h"
#include "commands/RotEndCommand.h"

class ViewModel: public Notification {
public:
    ViewModel();

    ~ViewModel();

    void init();

    void setCubeModel(std::shared_ptr<Cube> cube);

    std::shared_ptr<cubes_t> getCubeData();
    std::shared_ptr<CubeSteps> getSteps();
    
    std::shared_ptr<ICommandBase> getRotateCmd();
    std::shared_ptr<ICommandBase> getResetCmd();
    std::shared_ptr<ICommandBase> getRandomCmd();
    std::shared_ptr<ICommandBase> getSaveCmd();
    std::shared_ptr<ICommandBase> getLoadCmd();
    std::shared_ptr<ICommandBase> getSolveCmd();
    std::shared_ptr<ICommandBase> getStopCmd();
    std::shared_ptr<ICommandBase> getRotEndCmd();

private:
    // properties
    std::shared_ptr<Cube> m_pCube;
    std::shared_ptr<CubeSteps> m_pRSteps;

    // commands
    std::shared_ptr<RotateCommand> m_pRotateCommand;
    std::shared_ptr<ResetCommand> m_pResetCommand;
    std::shared_ptr<RandomCommand> m_pRandomCommand;
    std::shared_ptr<SaveCommand> m_pSaveCommand;
    std::shared_ptr<LoadCommand> m_pLoadCommand;
    std::shared_ptr<SolveCommand> m_pSolveCommand;
    std::shared_ptr<StopCommand> m_pStopCommand;
    std::shared_ptr<RotEndCommand> m_pRotEndCommand;

private:
    friend class RotateCommand;
    friend class ResetCommand;
    friend class RandomCommand;
    friend class SolveCommand;
    friend class StopCommand;
    friend class SaveCommand;
    friend class LoadCommand;
    friend class RotEndCommand;
};

#endif