#include "notification.h"

#include <QApplication>
#include <QPainter>

#include <QtMultimedia/QSound>

Notification::Notification(const std::string &sTitle)
{
    setWindowFlags(Qt::FramelessWindowHint |
                   Qt::Tool |
                   Qt::WindowStaysOnTopHint);

    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);

    m_Animation.setTargetObject(this);
    m_Animation.setPropertyName("m_Opacity");

    m_moveAnimation.setTargetObject(this);
    m_moveAnimation.setPropertyName("geometry");

    m_Label.setStyleSheet("padding: 1em; color: white;");
    m_Label.setText(sTitle.c_str());

    m_Layout.addWidget(&m_Label);
    setLayout(&m_Layout);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Notification::hide);

    adjustSize();
    resize(300, height());
}

Notification::Notification(const std::string &sTitle, const QPoint &pos)
    : Notification(sTitle)
{
    setPosition(pos);
}

Notification::~Notification()
{

}

void
Notification::mousePressEvent(QMouseEvent* event)
{
    Q_UNUSED(event);

   // QSound::play("/home/daniela/notification/sound/notification.wav");
    hide();
}

void
Notification::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect roundedRect;
    roundedRect.setX(rect().x() + 5);
    roundedRect.setY(rect().y() + 5);
    roundedRect.setWidth(rect().width() - 10);
    roundedRect.setHeight(rect().height() - 10);

    painter.setBrush(QBrush(QColor(0,0,0,180)));
    painter.setPen(Qt::NoPen);

    painter.drawRoundedRect(roundedRect, 10, 10);
}

double
Notification::getOpacity() const
{
    return m_Opacity;
}

void
Notification::setOpacity(double opacity)
{
    m_Opacity = opacity;
    setWindowOpacity(opacity);
}

void
Notification::show()
{
    setOpacity(0.0);
    QWidget::show();

    m_Animation.setDuration(150);
    m_Animation.setStartValue(0.0);
    m_Animation.setEndValue(1.0);
    m_Animation.start();
    timer->start(5000);

    QSound::play(":/notification.wav");
}

void
Notification::hide()
{
    timer->stop();
    m_Animation.setDuration(1000);
    m_Animation.setStartValue(1.0);
    m_Animation.setEndValue(0.0);
    m_Animation.start();
    emit hidden(this);
}

void
Notification::setPosition(const QPoint &pos)
{
    setGeometry(pos.x(), pos.y(), width(), height());
}

void
Notification::moveUp(const QPoint &pos)
{
    m_moveAnimation.setDuration(500);
    m_moveAnimation.setStartValue(geometry());
    m_moveAnimation.setEndValue(QRect(pos.x(), pos.y(), width(), height()));
    m_moveAnimation.start();
}

QPoint
Notification::getPosition() const
{
    return geometry().topLeft();
}
