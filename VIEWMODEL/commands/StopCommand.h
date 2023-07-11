#ifndef STOPCOMMAND_H
#define STOPCOMMAND_H

#include "../../COMMON/ICommandBase.h" // common

class ViewModel;

class StopCommand: public ICommandBase {
public:
    StopCommand(ViewModel* pVM);
    
    void setParameter(const std::any& param);
    void exec();

private:
    ViewModel* m_pVM;
};


#endif