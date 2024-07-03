#include "notificationmanager.h"

#include <QApplication>
#include <QScreen>

#include <QtMultimedia/QSound>
#include <iostream>

NotificationManager::NotificationManager()
{
    const QRect g = QApplication::screens().front()->geometry();
    m_iPosX = g.width() - 300 - 36;
    m_iPosY = 36;
}

NotificationManager::~NotificationManager()
{

}

void
NotificationManager::addNotification(std::unique_ptr<Notification> pNotification)
{
    Notification* p = pNotification.get();
    connect(p, &Notification::hidden, this, &NotificationManager::notificationClosed);
    m_vpActive.push_back(std::move(pNotification));
    QSound::play("/home/daniela/notification/sound/notification.wav");
    p->setPosition(QPoint(m_iPosX, m_iPosY));
    p->show();
    m_iPosY += 5 + p->height();
}

void
NotificationManager::notificationClosed(Notification* pNotification)
{
    auto it = m_vpActive.begin();
    auto end = m_vpActive.end();
    unsigned iPos = 0;
    bool bFound = false;
    QPoint last;

    while (it != end)
    {
        if (it->get() == pNotification)
        {
            last = it->get()->getPosition();
            m_vpActive.erase(it);
            bFound = true;
            break;
        }

        iPos++;
        ++it;
    }

    if (bFound)
    {
        for (unsigned i = iPos; i < m_vpActive.size(); i++)
        {
            m_vpActive[i]->moveUp(last);
            last = m_vpActive[i]->getPosition();
        }
    }
}
