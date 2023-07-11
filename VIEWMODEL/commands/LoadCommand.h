#ifndef LOADCOMMAND_H
#define LOADCOMMAND_H

#include <string>
#include <fstream>

#include "../../COMMON/ICommandBase.h" // common

class ViewModel;

class LoadCommand: public ICommandBase {
public:
    LoadCommand(ViewModel* pVM);
    
    void setParameter(const std::any& param);
    void exec();

private:
    ViewModel* m_pVM;
    std::string m_fileName;
};


#endif