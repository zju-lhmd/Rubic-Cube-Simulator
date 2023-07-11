#include "RandomCommand.h"

#include "../ViewModel.h"

RandomCommand::RandomCommand(ViewModel* pVM): m_pVM(pVM)
{
}

void RandomCommand::setParameter(const std::any& param)
{
    return ;
}

void RandomCommand::exec()
{
    // randomize cube state
    m_pVM->m_pCube->randomCube();
    m_pVM->notifyAllObservers(1); // TODO: message
}