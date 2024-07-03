#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPropertyAnimation>
#include <QTimer>

class Notification : public QWidget
{
    Q_OBJECT

public:
    Notification(const std::string &sTitle, const QPoint &pos);
    Notification(const std::string &sTitle);

    ~Notification();

    void show();
    void hide();
    void setPosition(const QPoint &pos);
    QPoint getPosition() const;
    void moveUp(const QPoint &pos);

signals:
    void hidden(Notification* pN);

protected:
    void mousePressEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent *event);

private:
    QLabel m_Label;
    QGridLayout m_Layout;
    QPropertyAnimation m_Animation;
    QPropertyAnimation m_moveAnimation;
    double m_Opacity;
    QTimer *timer;

    Q_PROPERTY(double m_Opacity READ getOpacity WRITE setOpacity)

    double getOpacity() const;
    void setOpacity(double opacity);

};

#endif // NOTIFICATION_H
