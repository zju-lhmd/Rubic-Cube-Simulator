#ifndef VIEWMODELSINK_H
#define VIEWMODELSINK_H

#include <string>

#include "../../COMMON/INotification.h" // common
#include "../../COMMON/types.h" // common

class ViewModel;

class ViewModelSink: public INotification {
public:
    ViewModelSink(ViewModel* pVM);

    void notify(const std::any& msg);
    
private:
    ViewModel* m_pVM;
};

#endif