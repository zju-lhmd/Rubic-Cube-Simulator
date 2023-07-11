#ifndef INOTIFICATION_H
#define INOTIFICATION_H

#include <any>

class INotification {
public:
    virtual void notify(const std::any& msg) = 0; // react to notification
};

#endif