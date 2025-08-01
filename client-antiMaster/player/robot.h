#ifndef ROBOT_H
#define ROBOT_H

#include "player.h"
#include <QObject>

class Robot : public Player
{
    Q_OBJECT
public:
    //声名父类的继承构造函数
   using Player::Player;
   explicit Robot(QObject* parent = nullptr);
   void prepareCallLord() override;
   void preparePlayHand() override;
   //考虑叫地主
   void thinkCallLord() override;
   void thinkPlayHand() override;
};

#endif // ROBOT_H
