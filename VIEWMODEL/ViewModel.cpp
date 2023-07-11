#include "ViewModel.h"

#include "commands/RotateCommand.h"
#include "commands/ResetCommand.h"
#include "commands/RandomCommand.h"
#include "commands/SolveCommand.h"
#include "commands/StopCommand.h"
#include "commands/SaveCommand.h"
#include "commands/LoadCommand.h"
#include "sinks/ViewModelSink.h"

ViewModel::ViewModel(): m_pResetCommand(std::make_shared<ResetCommand>(this)),
						m_pRandomCommand(std::make_shared<RandomCommand>(this)),
						m_pRotateCommand(std::make_shared<RotateCommand>(this)),
						m_pSolveCommand(std::make_shared<SolveCommand>(this)),
						m_pStopCommand(std::make_shared<StopCommand>(this)),
						m_pSaveCommand(std::make_shared<SaveCommand>(this)),
						m_pLoadCommand(std::make_shared<LoadCommand>(this)),
						m_pRSteps(std::make_shared<CubeSteps>()),
						m_pVMS(std::make_shared<ViewModelSink>(this))
{
	init();
}

ViewModel::~ViewModel()
{
}

void ViewModel::init()
{
	srand(clock());
}

void ViewModel::setCubeModel(std::shared_ptr<Cube> cube)
{
	m_pCube = cube;
}

std::shared_ptr<INotification> ViewModel::getSink()
{
	return m_pVMS;
}

std::shared_ptr<cubes_t> ViewModel::getCubeData()
{
	return m_pCube->getCubeData();
}

std::shared_ptr<CubeSteps> ViewModel::getSteps()
{
	return m_pRSteps;
}

std::shared_ptr<ICommandBase> ViewModel::getRotateCmd()
{
	return m_pRotateCommand;
}

std::shared_ptr<ICommandBase> ViewModel::getResetCmd()
{
	return m_pResetCommand;
}

std::shared_ptr<ICommandBase> ViewModel::getRandomCmd()
{
	return m_pRandomCommand;
}

std::shared_ptr<ICommandBase> ViewModel::getSaveCmd()
{
	return m_pSaveCommand;
}

std::shared_ptr<ICommandBase> ViewModel::getLoadCmd()
{
	return m_pLoadCommand;
}

std::shared_ptr<ICommandBase> ViewModel::getSolveCmd()
{
	return m_pSolveCommand;
}

std::shared_ptr<ICommandBase> ViewModel::getStopCmd()
{
	return m_pStopCommand;
}