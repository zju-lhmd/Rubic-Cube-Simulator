#ifndef RANDOMCOMMAND_H
#define RANDOMCOMMAND_H

#include "../../COMMON/ICommandBase.h" // common

class ViewModel;

class RandomCommand: public ICommandBase {
public:
    RandomCommand(ViewModel* pVM);
    
    void setParameter(const std::any& param);
    void exec();

private:
    ViewModel* m_pVM;
};


#endif