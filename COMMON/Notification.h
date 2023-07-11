#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <any>
#include <vector>

#include "INotification.h"

class Notification {
public:
    void clear()
    {
        m_observers.clear();
    }

    void addObserver(const std::shared_ptr<INotification>& ntf)
    {
        m_observers.push_back(ntf);
    }

    void removeObserver(const std::shared_ptr<INotification>& ntf)
    {
        for(auto it = m_observers.begin(); it != m_observers.end(); ++it)
            if(*it == ntf) {
                m_observers.erase(it);
                return ;
            }
    }

    void notifyAllObservers(const std::any& msg)
    {
        // send notification to every observer
        for(auto& observer : m_observers)
            observer->notify(msg);
    }
private:
    // observers will receive notifications when propoerties or other things changed
    std::vector<std::shared_ptr<INotification>> m_observers;
};


#endif