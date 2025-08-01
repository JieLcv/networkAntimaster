#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "cards.h"
#include "bgmcontrol.h"

class Player : public QObject
{
    Q_OBJECT
public:
    enum Role{Lord, Farmer};            //角色
    enum Sex{Man, Woman};               //性别
    enum Direction{left, Right};        //头像的显示方位
    enum Type{Robot, User, Unknown};    //玩家类型
    explicit Player(QObject *parent = nullptr);
    explicit Player(QString name, QObject *parent = nullptr);

    //名字
    void setName(QString name);
    QString getName();
    //角色
    void setRole(Role role);
    Role getRole();
    //性别
    void setSex(Sex sex);
    Sex getSex();
    //头像显示方位
    void setDirection(Direction direction);
    Direction getDirection();
    //玩家类型
    void setType(Type type);
    Type getType();
    //玩家分数
    void setScore(int score);
    int getScore();
    //游戏结果
    void setWin(bool flag);
    bool isWin();
    //提供当前对象的上家/下家对象
    void setPrePlayer(Player* player);
    void setNextPlayer(Player* player);
    Player* getPrePlayer();
    Player* getNextPlayer();
    //叫地主/抢地主
    void grabLordBet(int point);
    //存储扑克牌(发牌的时候得到的)
    void storeDispatchCard(Card& card);
    void storeDispatchCard(Cards& cards);
    //得到所有的牌
    Cards getCards();
    //清空玩家手中的牌
    void clearCards();
    //出牌
    void playHand(Cards& cards);
    //设置出牌的玩家以及已经待处理的扑克牌
    void setPendingInfo(Player* player, Cards& cards);
    void clearPendingInfo();
    Player* getPendPlayer();
    Cards getPendCards();
    //存储出牌玩家对象和打出的牌
    void storePendingInfo(Player *player, Cards &cards);
    BGMControl *getBgm();
    //虚函数
    virtual void prepareCallLord();
    virtual void preparePlayHand();
    virtual void thinkCallLord();
    virtual void thinkPlayHand();

protected:
    QString m_name;
    Role m_role;
    Sex m_sex;
    Direction m_direction;
    Type m_type;
    int m_score;
    bool m_isWin;
    Player* m_prev;
    Player* m_next;
    Cards m_cards;
    Cards m_pendCards;
    Player* m_pendPlayer;
    BGMControl *m_bgm;


signals:
    //通知游戏控制类，处理下注分数
    void notifyGrapLordBet(Player *player, int bet);
    //通知游戏控制类已经出牌
    void notifyPlayHand(Player *player, Cards card);
    //通知已经发牌了
    void notifyPickCards(Player *player, Cards card);

public slots:
};

#endif // PLAYER_H
