#include "ResetCommand.h"

#include "../ViewModel.h"

ResetCommand::ResetCommand(ViewModel* pVM): m_pVM(pVM)
{
}

void ResetCommand::setParameter(const std::any& param)
{
    return ;
}

void ResetCommand::exec()
{
    // init cube state
    m_pVM->m_pCube->init();
    m_pVM->notifyAllObservers(1); // TODO: message
}