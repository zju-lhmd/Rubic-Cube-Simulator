#include "RotEndCommand.h"

#include "../ViewModel.h"

RotEndCommand::RotEndCommand(ViewModel* pVM): m_pVM(pVM)
{
}
    
void RotEndCommand::setParameter(const std::any& param)
{
    m_method = std::any_cast<CubeRotateMethod>(param);
}

void RotEndCommand::exec()
{
    m_pVM->m_pCube->doMethod(m_method);
}