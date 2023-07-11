#include "SolveCommand.h"

#include "../ViewModel.h"

SolveCommand::SolveCommand(ViewModel* pVM): m_pVM(pVM)
{
}
    
void SolveCommand::setParameter(const std::any& param)
{
	return ;
}

void SolveCommand::exec()
{
	return;
}
