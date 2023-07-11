#ifndef MAINWINDOWSINK_H
#define MAINWINDOWSINK_H

#include <string>

#include "../../COMMON/INotification.h" // common

class MainWindow;

class MainWindowSink: public INotification {
public:
    MainWindowSink(MainWindow* pV);

    void notify(const std::any& msg);
    
private:
    MainWindow* m_pV;
};

#endif