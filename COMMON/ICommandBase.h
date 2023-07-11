#ifndef ICOMMANDBASE_H
#define ICOMMANDBASE_H

#include <any>

class ICommandBase {
public:
    ICommandBase() {}
    virtual ~ICommandBase() {}

    virtual void setParameter(const std::any& param) = 0;
    virtual void exec() = 0; // execute command
};


#endif