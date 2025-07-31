#ifndef ROBOTGRABLORD_H
#define ROBOTGRABLORD_H

#include <QRunnable>
#include "player.h"

//使用多线程的原因，玩家在抢地主的同时，其他玩家可能要做别的事情。
class RobotGrabLord : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit RobotGrabLord(Player *player, QObject *parent = 0);
protected:
   void run();
private:
   Player *m_player;

signals:

public slots:
};

#endif // ROBOTGRABLORD_H
