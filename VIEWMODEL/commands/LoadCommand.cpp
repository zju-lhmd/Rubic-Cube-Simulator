#include "LoadCommand.h"

#include "../ViewModel.h"

LoadCommand::LoadCommand(ViewModel* pVM): m_pVM(pVM), m_fileName()
{
}

void LoadCommand::setParameter(const std::any& param)
{
    m_fileName = std::any_cast<std::string>(param);
}

void LoadCommand::exec()
{
    try {
        // open file
		std::ifstream file(m_fileName);
		if (file.is_open()) {
			std::string line;
			getline(file, line);
			m_pVM->m_pCube->deserialize(line);
			file.close();
		}
        // if not open, abort
	}catch(const CubeError &err) {
        return ; // abort
	}
	m_pVM->notifyAllObservers(1); // TODO: message
}
