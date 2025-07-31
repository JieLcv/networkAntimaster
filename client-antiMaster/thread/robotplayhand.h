#ifndef ROBOTPLAYHAND_H
#define ROBOTPLAYHAND_H

#include <QRunnable>
#include "player.h"
//使用多线程的原因，玩家在出牌的同时，其他玩家可能要做别的事情，例如玩家拖动游戏窗口。
class RobotPlayHand : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit RobotPlayHand(Player *player, QObject *parent = 0);
protected:
    void run() override;
private:
    Player *m_player;
signals:

public slots:
};

#endif // ROBOTPLAYHAND_H
