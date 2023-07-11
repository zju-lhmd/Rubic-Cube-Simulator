#include "StopCommand.h"

#include "../ViewModel.h"

StopCommand::StopCommand(ViewModel* pVM): m_pVM(pVM)
{
}
    
void StopCommand::setParameter(const std::any& param)
{
    return ;
}

void StopCommand::exec()
{
    m_pVM->notifyAllObservers(0);
}
