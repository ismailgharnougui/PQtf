#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include "notification.h"
#include <vector>
#include <memory>

#include <QObject>

class NotificationManager : public QObject
{
    Q_OBJECT

public:
    NotificationManager();
    virtual ~NotificationManager();

    void addNotification(std::unique_ptr<Notification> pNotification);

private:
    int m_iPosX;
    int m_iPosY;

    std::vector<std::unique_ptr<Notification>> m_vpActive;
private slots:
    void notificationClosed(Notification* pNotification);

};

#endif // NOTIFICATIONMANAGER_H
