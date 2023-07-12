#ifndef SOLVECOMMAND_H
#define SOLVECOMMAND_H

#include "../../COMMON/ICommandBase.h" // common
#include "../solver/CubeSolver.h" // viewmodel
#include "../solver/ReduceFilter.h" // viewmodel
#include "../solver/NoXYZFilter.h" // viewmodel

class ViewModel;

class SolveCommand: public ICommandBase {
public:
    SolveCommand(ViewModel* pVM);
    
    void setParameter(const std::any& param);
    void exec();

private:
    ViewModel* m_pVM;
    std::string m_fileName;
};


#endif