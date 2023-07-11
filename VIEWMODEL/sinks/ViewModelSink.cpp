#include "ViewModelSink.h"

#include "../ViewModel.h"

ViewModelSink::ViewModelSink(ViewModel* pVM): m_pVM(pVM)
{
}

void ViewModelSink::notify(const std::any& msg)
{
    // update model state
    CubeRotateMethod method = std::any_cast<CubeRotateMethod>(msg);
    m_pVM->m_pCube->doMethod(method);
    return ;
}