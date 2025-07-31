#ifndef GAMECONTROL_H
#define GAMECONTROL_H


#include <QObject>
#include "robot.h"
#include "userplayer.h"
#include "cards.h"

struct BetRecord
{
    BetRecord()
    {
        reset();
    }
    void reset()
    {
        player = nullptr;
        bet = 0;
        times = 0;
    }

    Player* player;
    int bet;
    int times; //第几次叫地主
};

class GameControl : public QObject
{
    Q_OBJECT
public:
    //游戏状态
    enum GameStatus
    {
        DispatchCard,
        CallingLord,
        playingHand
    };
    //玩家状态
    enum PlayerStatus
    {
        ThinkingForCallLord,
        ThinkingForPlayHand,
        Winning
    };

    explicit GameControl(QObject *parent = 0);
    //初始化玩家
    void playerInit();
    //初始化扑克牌
    void initAllCards();
    //每次发一张牌
    Card takeOneCard();
    //得到最后的三张牌
    Cards getSurplusCards();
    //重置卡牌数据
    void resetCardData();

    //得到玩家的实例对象
    Robot* getLeftRobot();
    Robot* getRightRobot();
    UserPlayer* getUserPlayer();
    void setCurrentPlayer(Player *player);
    Player* getCurrentPlayer();

    //得到出牌玩家和打出的牌
    Player* getPendPlayer();
    Cards getPendCards();

    //准备叫地主
    void startLordCard();
    //成为地主
    void becomeLord(Player* player, int bet);
    //清空所有玩家得分
    void clearPlayerScore();
    //处理叫地主
    void onGrabBet(Player *player, int bet);
    //得到玩家下注的最高分数
    int getPlayerMaxBet();
    //处理出牌
    void onPlayHand(Player *player, Cards cards);
    //设置当前玩家
    void setCurrentPlayer(int index);
private:
    Robot* m_robotLeft;
    Robot* m_robotRight;
    UserPlayer* m_user;
    Player* m_currPlayer;
    Cards m_pendCards;
    Player* m_pendPlayer;
    Cards m_allCards;
    BetRecord m_betRecord;
    int m_curBet;

signals:
    //通知主界面显示和隐藏叫分按钮
    void playerStatusChanged(Player* player, PlayerStatus statue);
    //通知主界面玩家抢地主了，用于在gamepanel显示信息(不抢，叫地主，抢地主)
    void notifyGrapLordBet(Player *player, int bet, bool flag);
    //游戏状态变化，通知主界面
    void gameStatusChanged(GameStatus status);
    //通知主界面出牌了
    void notifyPlayHand(Player *player, Cards &cards);
    //通知玩家,存储最近出的牌
    void pendingInfo(Player *player, Cards &cards);
public slots:
};

#endif // GAMECONTROL_H
