#include "SaveCommand.h"

#include "../ViewModel.h"

SaveCommand::SaveCommand(ViewModel* pVM): m_pVM(pVM), m_fileName()
{
}

void SaveCommand::setParameter(const std::any& param)
{
    m_fileName = std::any_cast<std::string>(param);
}

void SaveCommand::exec()
{
    // get serialized cube data
    std::string data = m_pVM->m_pCube->serialize();
    // open file
    std::ofstream file(m_fileName);
    if (file.is_open()) {
        file << data;
        file.close();
    }
    // if file not open, abort
}