#ifndef USERPLAYER_H
#define USERPLAYER_H

#include "player.h"
#include <QObject>

class UserPlayer : public Player
{
    Q_OBJECT
public:
    //声名父类的继承构造函数
    using Player::Player;
    explicit UserPlayer(QObject* parent = nullptr);
    void prepareCallLord() override;
    void preparePlayHand() override;
signals:
    void startCountDown();
};

#endif // USERPLAYER_H
