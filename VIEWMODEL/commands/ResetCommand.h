#ifndef RESETCOMMAND_H
#define RESETCOMMAND_H

#include "../../COMMON/ICommandBase.h" // common

class ViewModel;

class ResetCommand: public ICommandBase {
public:
    ResetCommand(ViewModel* pVM);
    
    void setParameter(const std::any& param);
    void exec();

private:
    ViewModel* m_pVM;
};


#endif