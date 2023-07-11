#ifndef ROTATECOMMAND_H
#define ROTATECOMMAND_H

#include <string>

#include "../../COMMON/ICommandBase.h" // common
#include "../../COMMON/utilities.h" // common
#include "../../COMMON/types.h" // common

class ViewModel;

class RotateCommand: public ICommandBase {
public:
    RotateCommand(ViewModel* pVM);
    
    void setParameter(const std::any& param);
    void exec();

private:
    ViewModel* m_pVM;
    std::string m_method;

    static const std::map<std::string, CubeRotateMethod> nameToMethod;
};


#endif