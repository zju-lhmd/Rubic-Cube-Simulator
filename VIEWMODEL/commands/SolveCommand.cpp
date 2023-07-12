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
	// stop any rotation right now
	m_pVM->notifyAllObservers(0);
	Cube cpyCube(*(m_pVM->m_pCube));
	CubeSolver solver(cpyCube);
	// solve cubes
	solver.solve();
	CubeSteps steps = solver.GetSteps();
	// optimize steps
	steps = ReduceFilter::Filter(steps);
	steps = NoXYZFilter::Filter(steps);
	steps = ReduceFilter::Filter(steps);
	// start play steps
	*m_pVM->m_pRSteps = steps;
	m_pVM->notifyAllObservers(2);
}
