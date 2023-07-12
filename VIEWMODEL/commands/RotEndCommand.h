#ifndef ROTENDCOMMAND_H
#define ROTENDCOMMAND_H

#include "../../COMMON/ICommandBase.h" // common
#include "../../COMMON/types.h" // common

class ViewModel;

class RotEndCommand: public ICommandBase {
public:
    RotEndCommand(ViewModel* pVM);
    
    void setParameter(const std::any& param);
    void exec();

private:
    ViewModel* m_pVM;
    CubeRotateMethod m_method;
};


#endif