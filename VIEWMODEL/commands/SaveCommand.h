#ifndef SAVECOMMAND_H
#define SAVECOMMAND_H

#include <string>
#include <fstream>

#include "../../COMMON/ICommandBase.h" // common

class ViewModel;

class SaveCommand: public ICommandBase {
public:
    SaveCommand(ViewModel* pVM);
    
    void setParameter(const std::any& param);
    void exec();

private:
    ViewModel* m_pVM;
    std::string m_fileName;
};


#endif