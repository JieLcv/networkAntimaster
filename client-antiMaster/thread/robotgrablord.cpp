#include "robotgrablord.h"
#include "QDebug"
#include <QThread>

RobotGrabLord::RobotGrabLord(Player *player, QObject *parent) : QObject(parent), QRunnable()
{
    m_player = player;
    setAutoDelete(true);
}

void RobotGrabLord::run()
{
    QThread::msleep(2000); //msleep是线程类的静态成员函数
    m_player->thinkCallLord();
}
