#ifndef SOLVECOMMAND_H
#define SOLVECOMMAND_H

#include <string>
#include "../../COMMON/ICommandBase.h" // common

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